#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "taylor.h"

int main(void){

	//TESTE 1:
	
	double x = 1.0012;
	double resultado = fsqrt(x);
	double erro = fsqrt_erro(x);
	printf("Raiz de %lf = %lf\n", x, resultado);
	printf("Erro maximo: %lf\n", erro);
	printf("Erro encontrado: %.16g\n", fabs (sqrt(1.0012) - resultado));
	
	
	// TESTE 2:
	/*double x = 0.001;
	double erro = fcossin_erro(x);
	double resultado = fcossin(x);
	
	printf("Cos(%lf) + 2sin(%lf) = %.12g\n", 2.0*x, x, resultado);
	printf("Erro maximo: %.12g\n", erro);
	printf("Erro encontrado: %.16g\n", fabs(cos(0.002) + 2.0*sin(0.001) - resultado));
	*/
	
	return 0;
}
