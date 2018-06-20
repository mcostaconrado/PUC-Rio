#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "interp.h"
#define n 6
#define M_PI 3.14159265358979323846

int main(){
	int i;
	double x = 1;
	double* xi = Chebyshev (n, 0.0, M_PI/2.0);
	
	puts("\nAmostras de Chebyshev:\n");
	for (i = 0; i < n; i++){ 
		printf("x%i = %lf \n", i, xi[i]);
	}
	
	double* bi = NewtonCoef (n, xi, cos);
	

	
	puts("\n\nCoeficientes de Newton: \n");
	
	for (i = 0; i< n; i++){ 
		printf("b%i: %lf \n", i, bi[i]);
	}
	
	scanf("%lf", &x);
	while (x != -10){
		NewtonAval (n, xi, bi, x);
		scanf("%lf", &x);
	}

	return 0;	
}
