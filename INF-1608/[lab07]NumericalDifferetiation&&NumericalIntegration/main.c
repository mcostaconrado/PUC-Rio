#include <stdio.h>
#include <math.h>
#include "integral.h"
#define PI 3.14159265359

double f(double x)
{
	return (cos(x) - 2*sin(x));
}

double fl(double x)
{
	return(- sin(x) - 2*cos(x));
}

double f2(double x)
{
	return (x / sqrt(pow(x,2) + 9 ));
}

double f3(double x)
{
	return(pow(x, 2)*(log(x)));
}

double f4(double x)
{
	return(pow(x, 2)*(sin(x)));
}

int main(void)
{
	double x = 0.178;
	double a = 0, b = 1;
	double h = h_otimo(f, fl, x);
	printf("H_OTIMO: %.12lf\n", h);


	for (int i = 1; i <= 12; i++){
		printf("Valor com simpson -> h = 10^-%d: %.12lf\n", i, simpson (fl, a, b, 10));

	}
}