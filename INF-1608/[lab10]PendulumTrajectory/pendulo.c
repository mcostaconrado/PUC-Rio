#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pendulo.h"
#define min(a,b) a<b?a:b
#define G 9.8
#define L 10
#define H 0.001

/*

theta_t = theta_0*cos(kt)
w_t = -theta_0*k*sen(kt) 

*/


/*euler : x(t+h) = x(t) + hf(t,x(t))*/


/* DERIVADA :	w_t = -theta_0*k*sen(kt) 
		theta(t+h) = theta_0 + h* ( -theta_0*k*sen(k*t)

*/



double pendulo (double t, double h, double* theta, double* w){
	double w_0 = *w;	
	double k = sqrt(G/L);
	double theta_0 = *theta;

	*w = w_0 + h*(-G/L*sin(*theta));
	*theta = *theta + h*w_0;
	/**theta = theta_0 + h*(-theta_0*k*sin(k*t));
	*w = w_0 + h*w_0;*/

	return t + h;
}


double periodo (double theta_0){
	double inversoes = 0;
	double theta_i = theta_0;
	double w_i = 0;
	double t = 0;

	
	while (inversoes < 10){
		double w_aux = w_i;
		t = pendulo (t, H, &theta_i, &w_i);
		if (w_aux * w_i < 0) inversoes++;
	}
	return t/5.0;
}

double periodo_simplificado (double theta_0){
	return 2*M_PI*sqrt(L/G);
}


