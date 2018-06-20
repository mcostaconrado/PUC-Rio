#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gradconj.h"
#include "vetmat.h"
#define tol 0.00001

void COPIA_VETOR (double* dest, double* source, int n){
	int i;

	for(i = 0; i < n; i++)
		dest[i] = source[i];
}

int main(){
	double w = 1.25; //<<<<<<<<<<<<<<<< MUDAR FATOR DE SOBRE RELAXAMENTO AQUI!!!!!!!!!!!!!!!!1
	int k;
	int l;
	int i, j;
	int n = 0;
	double** A;
	double* b;
	double* x;

	scanf("%d ", &k); //casos de teste
	l= k;

	for (; k > 0; k--){
		double iteracoes;

		scanf("%d ", &n);

		double** A = matcria(n, n);
		double* x = vetcria(n);
		double* x_mudavel = vetcria(n);
		double* b = vetcria(n);


		for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				scanf("%lf ", &A[i][j]);
			}
		}

		for (i = 0; i < n; i++){
			scanf("%lf ", &x[i]);
		}

		COPIA_VETOR(x_mudavel, x, n);
		for (i = 0; i < n; i++){
			scanf("%lf ", &b[i]);
		}

		//GradConj (n, A, b, x, tol);
		//printf("\n\nvetor x: \n\n");
		//vetimprime(n, x, "%.10lf ");


		//matimprime(n, n, A, "%lf ");
		
		printf("\n\nGRADIENTE E CONJUGADO s/ Pré-Cond: \n%i iteracoes.\nResultado de x:\n", GradConj(n, A, b, x_mudavel, tol));
		vetimprime(n, x_mudavel, "%.10lf");
		COPIA_VETOR(x_mudavel, x, n);

		printf("\n\nGRADIENTE E CONJUGADO c/ Pré-Cond: \n%i iteracoes.\nResultado de x:\n", GradConjJacobi(n, A, b, x_mudavel, tol));
		vetimprime(n, x_mudavel, "%.10lf");
		COPIA_VETOR(x_mudavel, x, n);

		/*
		printf("\n");
		printf("COM GaussSeidel: \n%i iteracoes.\nResultado de x: \n", GaussSeidel(n, A, b, x_mudavel, tol));
		vetimprime(n, x_mudavel, "%lf");
		COPIA_VETOR(x_mudavel, x, n);
		
		printf("\n");
		printf("GaussSeidel com sobre-relaxamento: \nw = %.2lf.\n%i iteracoes.\nResultado de x: \n", w, SOR(n, A, b, x_mudavel, tol, w));
		vetimprime(n, x_mudavel, "%lf");
		COPIA_VETOR(x_mudavel, x, n);
		puts("\n\n");*/

		vetlibera(x);
		vetlibera(x_mudavel);
		vetlibera(b);
		matlibera(n, A);

	}

}
