/*
CONRADO COSTA 1710234

COMPILAÇÃO: gcc -o main main.c methiter.c vetmat.c
EXECUÇÃO: ./ < teste.txt


FORMATO DO ARQUIVO teste.txt:

%d <numero de sistemas>

%d <numero de linhas/colunas da matriz quadrada>

<matriz A>
%d %d .. %d 
%d %d .. %d
..
%d .. .. %d


<vetor x inicial>
%d .. %d

<vetor b>
%d .. %d



----------------xxxxxxxxxx-------------------

arquivo .txt do .pdf:

2


2

3 1
1 2

0 0

5 5



6

3	-1	0	0	0	0.5
-1	3	-1	0	0.5	0
0	-1	3	-1	0	0
0	0	-1	3	-1	0
0	0.5	0	-1	3	-1 
0.5 0 	0 	0 	-1 	3

0 0 0 0 0 0

2.5 1.5 1 1 1.5 2.5


----------------xxxxxxxxxx-------------------


*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methiter.h"
#include "vetmat.h"
#define tol 0.00000000001

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
		
		printf("COM JACOBI: \n%i iteracoes.\nResultado de x:\n", Jacobi(n, A, b, x_mudavel, tol));
		vetimprime(n, x_mudavel, "%lf");
		COPIA_VETOR(x_mudavel, x, n);

		printf("\n");
		printf("COM GaussSeidel: \n%i iteracoes.\nResultado de x: \n", GaussSeidel(n, A, b, x_mudavel, tol));
		vetimprime(n, x_mudavel, "%lf");
		COPIA_VETOR(x_mudavel, x, n);
		
		printf("\n");
		printf("GaussSeidel com sobre-relaxamento: \nw = %.2lf.\n%i iteracoes.\nResultado de x: \n", w, SOR(n, A, b, x_mudavel, tol, w));
		vetimprime(n, x_mudavel, "%lf");
		COPIA_VETOR(x_mudavel, x, n);
		puts("\n\n");

		vetlibera(x);
		vetlibera(x_mudavel);
		vetlibera(b);
		matlibera(n, A);

	}

	/*Jacobi(n, A, b, x, tol);
	puts("\n");*/


	//matimprime(n, n, A, "%lf");	
	//puts("\n");
	//vetimprime(n, x, "%lf");
	//puts("\n");
	//vetimprime(n, b, "%lf");
	//puts("\n");

}