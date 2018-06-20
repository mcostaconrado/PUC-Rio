#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pendulo.h"

double toRd (double degree){
	return 1/360.0 * degree * 2*M_PI;

}

int main(){
	
	printf("x = 1º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(1.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(1.)));
	
	printf("x = 3º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(3.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(3.)));

	printf("x = 5º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(5.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(5.)));

	printf("x = 10º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(10.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(10.)));

	printf("x = 30º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(30.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(30.)));

	printf("x = 60º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(60.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(60.)));

	printf("x = 90º\n");
	printf("NUMERICO: %lf\n", periodo(toRd(90.)));
	printf("SIMPLIFICADO: %lf\n\n", periodo_simplificado(toRd(90.)));


	return 0;
}
