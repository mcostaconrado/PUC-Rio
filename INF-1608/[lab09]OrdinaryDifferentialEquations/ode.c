#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ode.h"

double Euler (double t0, double t1, double h, double x0, double (*f) (double t, double x)){
	int n = (int)(t1-t0)/h;
	int i;
	double x_i = x0;
	double t_i = t0;



	for (i = 0; i<n; i++, t_i+= h){
		x_i = x_i + h*f(t_i, x_i);
	}

	return x_i;


}