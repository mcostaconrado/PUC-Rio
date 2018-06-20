#include <stdio.h>
#include <stdlib.h>
#include "bissecao.h"
#include <math.h>

#define GRAV 9.8
#define C 15.0
#define V 35.0
#define T 9.0

double func(double m){
	return GRAV*m/C * (1.0 - exp(-C/m*T)) - V;
}

double funcA(double x){
	return 2.0*x*x*x*x*x - 4.0*x*x + 1.0;
}

double funcB(double x){
	return sin(x) - 6.0 * x - 5.0;
}

double funcC(double x){
	return sin(x)/cos(x) + 5.0*x*x - x;
}

int main(){	
	int n;
	double* arr;
	
	arr = bissecao_multipla (-10.0, 10.0, 0.01, funcA, &n);
	
	printf("\nRaizes da equação 2x⁵ - 4x² + 1:\n\n");
	for (int i = 0; i<n; i++){
		printf("%dª: %.10g \n", i+1, arr[i]);
	}
	
	arr = bissecao_multipla (-10.0, 10.0, 0.01, funcB, &n);
	
	printf("\nRaizes da equação sen(x) - 6x - 5:\n\n");
	for (int i = 0; i<n; i++){
		printf("%dª: %.10g \n", i+1, arr[i]);
	}
	
	arr = bissecao_multipla (-10.0, 10.0, 0.000003, funcC, &n);
	
	printf("\nRaizes da equação tan(x) + 5x² - x:\n\n");
	for (int i = 0; i<n; i++){
		printf("%dª: %.10g \n", i+1, arr[i]);
	}
	
}
