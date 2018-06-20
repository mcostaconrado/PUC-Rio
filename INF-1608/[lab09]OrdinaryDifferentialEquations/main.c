#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ode.h"

double f(double t, double x){
	return t*x + t*t*t;

}

int main(){

	printf("com h = 0.1 -> %lf\n", Euler(0, 2.4, 0.1, -1, f));
	printf("com h = 0.01 -> %lf\n", Euler(0, 2.4, 0.01, -1, f));
	printf("com h = 0.001 -> %lf\n", Euler(0, 2.4, 0.001, -1, f));
	printf("com h = 0.0001 -> %lf\n", Euler(0, 2.4, 0.0001, -1, f));


	return 0;
}