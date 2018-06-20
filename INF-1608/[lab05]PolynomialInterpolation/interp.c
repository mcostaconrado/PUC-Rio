#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <malloc.h>
#include "interp.h"	

static double fat(int n){
	double fat = 1.0;
	while (n > 1){
		fat*= n;
		n--;
	}
	return fat;
}

static double reducao_quadrante(double x, double* sinal){
	double k = M_PI/2.0;
	double angulo = x;
	
	if (angulo < 0.0) 
		angulo = -angulo; // fç cosseno é par.
	
	if (angulo < k)
		*sinal = 1.0;
	else if (angulo <= 2.0*k){
		*sinal = -1.0;
		angulo = M_PI - angulo;
	}
	else if (angulo <= 3.0*k){
		*sinal = -1.0;
		angulo = angulo - M_PI;
	}
	else{
		*sinal = 1.0;
		angulo = 2*M_PI - angulo;
	}
	return angulo;
}

double* Chebyshev (int n, double a, double b){
	int i; 
	double beta=1;
	double* x = (double*) malloc (sizeof(double)*n);
	
	for (i = 0; i < n; i++){
		x[i] = 1.0/2.0*(b - a)*cos((beta*M_PI)/(2.0*n)) + 1.0/2.0*(a + b);
		beta+=2;
	}
	
	return x;
}

double* NewtonCoef (int n, double* xi, double (*f) (double)){

	double** difDiv = (double**) malloc (sizeof(double*)*n);
	double* coef = (double*) malloc (sizeof(double)*n);
	int i, j;
	
	for (i = 0; i<n; i++){
		difDiv[i] = (double*) malloc (sizeof(double)*n);
	}
	
	for (i = 0; i < n; i++){
		difDiv[i][0] = f(xi[i]);
	}
	
	coef[0] = difDiv[0][0];
	
	for (j = 1; j < n; j++){
		for (i = j; i < n; i++){
			difDiv[i][j] = (difDiv[i][j-1] - difDiv[i-1][j-1])/(xi[i] - xi[i-j]);
			if (i == j) coef[i] = difDiv[i][j];
		}
	}	

	for (i = 0; i < n; i++){
		free(difDiv[i]);
	}

	free(difDiv);	
	
	return coef;
}

double NewtonAval (int n, double* xi, double* bi, double x){
	int i; 
	double polinomio = bi[0];
	double aux = 1.;
	double sinal;
	double erromax = 0;
	double valor_real = cos(x);
	
	x = reducao_quadrante(x, &sinal);
	
	for (i = 1; i<n; i++){
		aux *= (x-xi[i-1]);
		polinomio += bi[i]*aux;
	}

	polinomio = polinomio*sinal;
	
	erromax = pow((M_PI/2.0 - 0.0)/2.0, n) / pow(2, n-1) * polinomio / fat(n);
	
	printf("\nValor encontrado: %lf\nValor real: %lf\n\nErro encontrado: %lf\nErro maximo: %lf\n", polinomio, valor_real, fabs(polinomio- valor_real), fabs(erromax));
	
	return polinomio;
}
