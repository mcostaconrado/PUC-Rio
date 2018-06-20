#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "vetmat.h"

double* vetcria (int n){
	double *p = (double*)malloc(sizeof(double)*n);
	if (p != NULL)
		return p;
	exit(1);
}

void vetlibera (double* v){
	free (v);
}

double escalar (int n, double* v, double* w){

	double escalar = 0;
	int i = 0;

	for(i = 0; i < n; i++)
		escalar += v[i]*w[i];

	return escalar;
}

double norma2 (int n, double* v){
	double soma2 = 0;
	int i = 0;
	for (i=0; i<n; i++)
		soma2 += v[i]*v[i];

	return sqrt(soma2);
}
/*
double norma2_diff (int n, double* v, double* w){
	double soma2 = 0;
	int i = 0;
	for (i=0; i<n; i++)
		soma2 += (v[i] - w[i]) * (v[i] - w[i]);

	return sqrt(soma2);
}
*/
int vetiguais (int n, double* v, double* w, double tol){
	int i = 0;
	for (i=0; i<n; i++){
		if (fabs(v[i] - w[i]) > tol)
			return 0;
	}
	return 1;
}

void vetimprime (int n, double* v, char* format){
	int i = 0;
	for (i=0; i<n; i++){
		printf(format, v[i]);
		printf("\n");
	}
}

double** matcria (int m, int n){
	int i;
	double** mat = (double**) malloc(sizeof(double*)*m);
	
	for (i = 0; i < m; i++)
		mat[i] = (double*)malloc(sizeof(double)*n);
	return mat;
}

void matlibera(int m, double** A) {
	int i;

	for (i = 0; i < m; i++)
		free(A[i]);

	free(A);
}

void transposta (int m, int n, double** A, double** T){
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			T[i][j] = A[j][i];
		}
	}
}

void multmv(int m, int n, double** A, double* v, double* w) {
	// MATRIZ A COM DIMENSÃO				MxN
	// VETOR MULTIPLICADOR v COM DIMENSÃO	n
	// VETOR RESULTADO w COM DIMENSÃO		m
	int i;

	for (i = 0; i < m; i++) {
		w[i] = escalar(n, A[i], v);
	}
}

void multmm(int m, int n, int q, double** A, double** B, double** C) {
	int i, j;
	double* res_aux = vetcria(m);
	double** B_transp = matcria(q, n);
	double** C_aux = matcria(q, m);

	transposta(n, q, B, B_transp);

	for (i = 0; i < q; i++) {
		multmv(m, n, A, B_transp[i], res_aux);

		for (j = 0; j < m; j++) {
			C_aux[i][j] = res_aux[j];
		}
	}
	matlibera(q, B_transp);
	vetlibera(res_aux);

	transposta(q, m, C_aux, C);

	matlibera(q, C_aux);
}

int matiguais(int m, int n, double** A, double** B, double tol) {
	int i, j;
	if (m == n) {
		for (i = 0; i < m; i++) {
			if (!vetiguais(n, A[i], B[i], tol))
				return 0;
		}
		return 1;
	}
	return 0;
}

void matimprime(int m, int n, double** A, char* format) {
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf(format, A[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}