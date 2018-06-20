#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"
#include "integral.h"

double DoubleSimpson (double a, double b, double (*f) (double x), double* v){
	double c = (a+b)/2.0;
	double sum;
	sum = fabs ( simpson(f, a, b, 1) - simpson(f,a,c,1) - simpson(f, c, b, 1) ) / 15;
	*v = sum + simpson (f,a,c,1) + simpson(f,c,b,1);
	return sum;
	
}

double AdaptiveSimpson (double a, double b, double (*f) (double x), double tol){
	double sum = 0;
	double erro = DoubleSimpson(a, b, f, &sum);
	if (erro < tol)
		return sum;
	else
		return AdaptiveSimpson(a, (a+b)/2.0, f, tol/2.0) + AdaptiveSimpson((a+b)/2.0, b, f, tol/2.0);

}

double Quadratura2 (double a, double b, double (*f) (double x)){
	double x[] = {-sqrt(1.0/3.0), sqrt(1.0/3.0)};
	double sum = 0;
	for (int i = 0; i<2; i++){
		sum+= f(0.5 * ((b-a)*x[i] + b + a)) * (b-a)*0.5;
	}
	return sum;
}

double Quadratura3 (double a, double b, double (*f) (double x)){
	double x[] = {-sqrt(3.0/5.0), 0, sqrt(3.0/5.0)};
	double c[] = {5.0/9.0, 8./9., 5./9.};
	double sum = 0;
	for (int i = 0; i<3; i++){
		sum+= c[i]*f(0.5 * ((b-a)*x[i] + b + a)) * (b-a)*0.5;
	}
	return sum;
}