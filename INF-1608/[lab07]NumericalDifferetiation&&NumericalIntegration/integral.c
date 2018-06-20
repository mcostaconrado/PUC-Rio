#include <stdio.h>
#include <math.h>
#include "integral.h"


double derivada(double (*f) (double x), double x, double h){
	return ((f(x+h) - f(x-h))/(2*h));
}




double h_otimo (double (*f) (double x), double (*fl) (double x), double x){
	double h;
	double erro = 100000000;	//erro inicializado com um valor grande para já ser pego na primeira iteração
	int i;

	for (i=1; i <= 12; i++){
		double erro_i, h_i;	// parâmetros de cada iteração
		h_i = pow(10, -i);	// h_i = 10⁻¹ ... 10⁻¹²
		erro_i = fabs(derivada(f, x, h) - fl(x));
		printf("erro_i = %lf\n", erro_i);
		if (erro_i < erro){	// se erro for menor
			erro = erro_i;	// fico com ele
			h = h_i;		// e com seu h
		}
	}

	return h;
}

double simpson (double (*f) (double), double a, double b, int n)
{
	int i;
	double h, sum, a_i;
	h = (b - a)/n;
	sum = 0;
	a_i = a;

	for(i = 0; i < n; i++)
	{
		sum += (h/6.0)*(f(a_i) + 4.0*f(a_i+(h/2.0)) + f(a_i+h));
		a_i += h;
	}

	//a_i -= h;
	return sum;
}
double pontomedio (double (*f) (double), double a, double b, int n)
{
	int i;
	double h, sum, w, a_i;

	h = (double) (b - a)/n;
	sum = 0;
	a_i = a;

	for(i=0; i < n; i++){

		w = a_i + h/2;
		sum += (h)*(f(w));
		a_i += h;
	}
	return sum;
}