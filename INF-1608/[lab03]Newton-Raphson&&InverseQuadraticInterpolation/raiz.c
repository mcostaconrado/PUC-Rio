#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raiz.h"

static double Crammer (double x0, double x1, double x2, double (*f) (double x)){
	double A[3][3];
	double Ac[3][3];
	double fx0 = f(x0); double fx1 = f(x1); double fx2 = f(x2);
	double detA, detAc;
	
	A[0][0] = fx0 * fx0;	A[0][1] = fx0;	A[0][2] = 1.0;
	A[1][0] = fx1 * fx1;	A[1][1] = fx1;	A[1][2] = 1.0;
	A[2][0] = fx2 * fx2;	A[2][1] = fx2;	A[2][2] = 1.0;
	
	Ac[0][0] = fx0 * fx0;	Ac[0][1] = fx0;	Ac[0][2] = x0;
	Ac[1][0] = fx1 * fx1;	Ac[1][1] = fx1;	Ac[1][2] = x1;
	Ac[2][0] = fx2 * fx2;	Ac[2][1] = fx2;	Ac[2][2] = x2;
	
	detA = (A[0][0]*A[1][1]*A[2][2]) + (A[0][1]*A[1][2]*A[2][0]) + (A[0][2]*A[1][0]*A[2][1]) - ((A[0][1]*A[1][0]*A[2][2]) + (A[0][0]*A[1][2]*A[2][1]) + (A[0][2]*A[1][1]*A[2][0]));
          
	detAc = (Ac[0][0]*Ac[1][1]*Ac[2][2]) + (Ac[0][1]*Ac[1][2]*Ac[2][0]) + (Ac[0][2]*Ac[1][0]*Ac[2][1]) - ((Ac[0][1]*Ac[1][0]*Ac[2][2]) + (Ac[0][0]*Ac[1][2]*Ac[2][1]) + (Ac[0][2]*Ac[1][1]*Ac[2][0]));
	
	return detAc/detA;
	
}

int NR (double x0, int p, double (*f) (double x), double (*fl) (double x), double* r){
	double tol = 0.5 * pow(10.0, -p);
	int i;
	double aprox = x0;
	double faprox = f(aprox);
	
	for (i = 0;  fabs(faprox) > tol && i <= 50; i++){
		if (faprox == 0.0){
			return 0;
		}
		
		aprox = aprox - faprox/fl(aprox);
		faprox = f(aprox);
	}
	
	*r = aprox;
	
	if (i > 50)
		return 0;
	
	
	return i;
	
}

int IQI (double x0, double x1, double x2, int p, double (*f) (double x), double* r){
	double tol = 0.5*pow(10.0, -p);
	int i;
	double c;
		
	for (i = 0; i <= 400; i++){
		c = Crammer(x0, x1, x2, f);
		if (fabs(f(c)) <= tol)
			break;
		x0 = x1;
		x1 = x2;
		x2 = c;		
	}
		
	*r = c;
	
	if (i > 400)
		return 0;
	
	
	return i;
}
















