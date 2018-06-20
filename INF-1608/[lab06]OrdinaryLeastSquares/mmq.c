#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <malloc.h>
#include "mmq.h"
#include "sistlinear.h"
#include "vetmat.h"

static int* vetcria_i (int n){
	int *p = (int*)malloc(sizeof(int)*n);
	if (p != NULL)
		return p;
	exit(1);
}

static void vetlibera_i (int* v){
	free (v);
}

void vetimprime_i (int n, int* v, char* format){
	int i = 0;
	for (i=0; i<n; i++){
		printf(format, v[i]);
		printf("\n");
	}
}

double* mmq (int m, int n, double** A, double* b){	
	int i, j;
	double** A_t = matcria(n, m);
	double** AA_t = matcria(m,m);
	double* A_tb = vetcria(n);
	double* x;
	int* permutacao;

	transposta (m, n, A, A_t);
	
	multmm (n, m, n, A_t, A, AA_t);			// lado direito do sistema  (At * A) 
	multmv(n, m, A_t, b, A_tb);						// lado esquerdo do sistema (At * b) 
	
	permutacao = fatoracao(m, AA_t);
	
	x = substituicao (n, AA_t, permutacao, A_tb);
	vetimprime(n, x, "%lf ");

	matlibera(n, A_t);
	matlibera(m, AA_t);
	vetlibera(A_tb);
	vetlibera_i(permutacao);

	return x;

}

double mmqNorma2 (int m, int n, double** A, double* b, double* x){
	int i;
	double* residuo = vetcria(m);
	double* Ax = vetcria(m); //matriz MxN X N vetor = vetor m
	double erro;
	
	multmv(m, n, A, x, Ax);
	
	
	for (i = 0; i < m; i++){
		residuo[i] = b[i] - Ax[i];
	}
	
	
	erro = norma2(m, residuo);
	
	vetlibera(residuo);
	vetlibera(Ax);
	
	return erro;
}

double concentracao (int n, double* t, double* c, double* pa, double* pb){
	int i, j;
	double** A = matcria(n, 2);
	double* x = vetcria(2);
	double* b = vetcria(n);
	double norma;
	
	for (i = 0; i < n; i++){
		A[i][0] = 1;
		A[i][1] = t[i];
		b[i] = log(c[i]/t[i]);
	}
	
	x = mmq(n, 2, A, b);
	
	*pa = exp(x[0]);
	*pb = x[1];
	
	norma =  mmqNorma2(n, 2, A, b, x);
	matlibera(n, A);
	vetlibera(x);
	vetlibera(b);
	
	return norma;
}








