#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "taylor.h"

static double fcos (double x){
	double aux = x;
	double zero = 1.0;
	double segundo = -1.0 / 2.0;
	
	return (zero + segundo*aux*aux );

}

static double fsin (double x){
	double aux = x;
	double primeiro = 1.0;
	double terceiro = -1.0 / 6.0;
	
	return (primeiro*aux + terceiro*aux*aux*aux);

}

double fsqrt (double x){
	double aux = x - 1.0;
	double zero = 1.0;
	double primeiro = 1.0 / 2.0 * 1.0 / 1.0;
	double segundo = -1.0 / 4.0 * 1.0 / 2.0;
	double terceiro = 3.0 / 8.0 * 1.0 / 6.0; terceiro = 1.0 / 16.0;
	
	return (zero + primeiro * aux + segundo * aux * aux + terceiro * aux * aux * aux);
}

double fsqrt_erro (double x){
	double quarto = -5.0 / 16.0 * 8.0;
	
	return fabs(quarto * 1.0 / (x*x*x*fsqrt(x)) );
}

double fcossin (double x){

	return fcos(2.0*x) + 2.0*fsin(x);
}

double fcossin_erro(double x){

	return fabs( 1.0 / 24.0 * fcos(2*x) * pow(M_PI, 4)) + fabs(1.0 / 12.0 * 2.0 * fsin(x) * pow(M_PI, 4) );
}
