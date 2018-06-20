#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bissecao.h"
#define PRECISAO 10

double bissecao (double a, double b, int p, double (*f) (double x)){
	double tol = 0.5 * pow (10.0, -p);
	int it = ceil ( log10((b-a)/tol) / log10(2.0) - 1 ); 
	int i;
	double c;
	double fc;
	
	for (i = 0; i < it; i++){
		c = (a+b)/2.0;
		fc = f(c);
		
		if (fabs(fc) == 0.0)
			break;
			
		else if (f(a)*fc < 0.0)
			b = c;
			
		else
			a = c;
	}
		
	return c;	
}

double* bissecao_multipla (double A, double B, double delta, double (*f) (double x), int* n){
	double a = A;
	double b = B;
	int intervalos = (B - A)/delta;
	int nRaizes = 0;
	double* vecGrande = (double*)malloc(sizeof(double)* intervalos); //esse vetor contem espaço para "intervalos" raizes (max)
	double* vecRaizes;
	
	int i;
	
	for (i = 1; i <= intervalos; i++){
		b = a + delta*i;
		
		if (f(a)*f(b) < 0){
			vecGrande[nRaizes] = bissecao(a, b, PRECISAO, f);
			nRaizes++;
		}
	
		a = b;
	}
	
	vecRaizes = (double*)malloc(sizeof(double)*nRaizes);
	(*n) = nRaizes;
	
	memcpy (vecRaizes, vecGrande, sizeof(double)*nRaizes);
	
	free(vecGrande);
	return vecRaizes;	
}
