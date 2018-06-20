#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"
#include "integral.h"

#define TOL 0.0000001


double f1(double x){
	return x/sqrt(x*x + 9);

}

double f2 (double x){
	return exp(-(x*x)/2.0);
}

double f3 (double x){
	return exp(-(x*x));
}

int main(){
	/*double x = 1;
	double hotimo = h_otimo (f, fl, x);
	double valorcorreto = fl(1);

	printf("h otimo: %.12lf\n\n", hotimo);

	printf("VALOR CORRETO> %.12lf\n\n", valorcorreto);

	for (int i = 1; i<13; i++){
		double h = pow(10, -i);
		double valor_i = derivada(f, x, h);

		printf("h = 10^-%i\n", i);
		printf("AVALIACAO DA DERIVADA: %.12lf \t erro: %.12lf\n\n", valor_i, fabs(valor_i - valorcorreto));

	}*/

	printf("TESTE DO METODO DE SIMPSON:\n\n");

	printf("fc 1: %.8lf\n", AdaptiveSimpson (0, 1, f1, TOL));
	printf("fc 2: %.8lf\n", 1.0/sqrt(2*M_PI)*AdaptiveSimpson (-1, 1, f2, TOL));
	printf("fc 3: %.8lf\n\n", 2.0/sqrt(M_PI)*AdaptiveSimpson (0, 3, f3, TOL));



	printf("TESTE DA QUADRATURA DE GAUSS: \n\n");
	printf("COM 2 AMOSTRAS: \n");
	printf("fc 1: %.8lf\n", Quadratura2 (0, 1, f1));
	printf("fc 2: %.8lf\n", 1.0/sqrt(2*M_PI)*Quadratura2 (-1, 1, f2));
	printf("fc 3: %.8lf\n\n", 2.0/sqrt(M_PI)*Quadratura2 (0, 3, f3));
	
	
	printf("COM 3 AMOSTRAS: \n");
	printf("fc 1: %.8lf\n", Quadratura3 (0, 1, f1));
	printf("fc 2: %.8lf\n", 1.0/sqrt(2*M_PI)*Quadratura3 (-1, 1, f2));
	printf("fc 3: %.8lf\n\n", 2.0/sqrt(M_PI)*Quadratura3 (0, 3, f3));
	

	

	return 0;
}