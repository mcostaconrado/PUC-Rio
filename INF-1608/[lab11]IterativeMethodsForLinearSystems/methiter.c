#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "methiter.h"
#include "vetmat.h"

static double norma2_diff (int n, double* v, double* w){
	double soma2 = 0;
	int i = 0;
	for (i=0; i<n; i++)
		soma2 += (v[i] - w[i]) * (v[i] - w[i]);

	return sqrt(soma2);
}

static void copia_vetor (double* dest, double* source, int n){
	int i;

	for(i = 0; i < n; i++)
		dest[i] = source[i];
}

int Jacobi (int n, double** A, double* b, double* x, double tol){
	int iteracoes;
	int norma = 1;
	int i, j;
	double* ultima_it = vetcria(n);

	for (iteracoes = 1; norma > tol; iteracoes++){
		copia_vetor(ultima_it, x, n);

		for (i = 0; i < n; i++){
			double lu_xk = 0;
			for (j = 0; j < n ; j++){
				if (i != j){
					lu_xk += A[i][j] * ultima_it[j];
				}
			}
			x[i] = (b[i] - lu_xk) / A[i][i];
		}
		norma = norma2_diff(n, ultima_it, x);
	}

	free (ultima_it);
	return iteracoes;

}

int GaussSeidel (int n, double** A, double* b, double* x, double tol){
	int iteracoes;
	int norma = 1;
	int i, j;
	double* ultima_it = vetcria(n);

	for (iteracoes = 1; norma > tol; iteracoes++){
		copia_vetor(ultima_it, x, n);

		for (i = 0; i < n; i++){
			double lu_xk = 0;
			for (j = 0; j < n ; j++){
				if (i != j){
					lu_xk += A[i][j] * x[j];
				}
			}
			x[i] = (b[i] - lu_xk) / A[i][i];
		}
		norma = norma2_diff(n, ultima_it, x);
	}
	free (ultima_it);
	return iteracoes;
}


int SOR (int n, double** A, double* b, double* x, double tol, double w){
	int iteracoes;
	int norma = 1;
	int i, j;
	double* ultima_it = vetcria(n);

	for (iteracoes = 1; norma > tol; iteracoes++){
		copia_vetor(ultima_it, x, n);

		for (i = 0; i < n; i++){
			double lu_xk = 0;
			for (j = 0; j < n ; j++){
				if (i != j){
					lu_xk += A[i][j] * x[j];
				}
			}
			x[i] = (b[i] - lu_xk) / A[i][i];
			x[i] = (1-w)*ultima_it[i] + w*x[i];
		}
		norma = norma2_diff(n, ultima_it, x);
	}
	free (ultima_it);
	return iteracoes;

}