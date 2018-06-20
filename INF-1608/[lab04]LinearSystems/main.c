#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "sistlinear.h"

double* vetcria_d (int n){
	double *p = (double*)malloc(sizeof(double)*n);
	if (p != NULL)
		return p;
	exit(1);
}

int* vetcria_i (int n){
	int *p = (int*)malloc(sizeof(int)*n);
	if (p != NULL)
		return p;
	exit(1);
}

void vetlibera_d (double* v){
	free (v);
}

void vetlibera_i (int* v){
	free (v);
}

void vetimprime_d (int n, double* v, char* format){
	int i = 0;
	for (i=0; i<n; i++){
		printf(format, v[i]);
		printf("\n");
	}
}

void vetimprime_i (int n, int* v, char* format){
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

void main(){
	//double** A = matcria(3, 3);
	int n, m;
	int i, j;
	double* x;
	int* perm_array;
	
	
	/*	
	
	//input.txt file be like (3x3 example):
	
	3 3
	
	... ... ...		}
	... ... ...		} 3x3 matrix
	... ... ...		}
	
	...						}	
	...						} b array
	...						}
		
	//compile with ./program < input.txt
	
	*/
	
	scanf("%d %d", &n, &m);
	
	double** A = matcria(n,m);
	double* b = vetcria_d(n);
	
	for (i=0; i<n; i++){
		for(j=0; j<m; j++){
			scanf("%lf ", &A[i][j]);
		}
	}
	
	for (i = 0; i < n; i++){
		scanf("%lf", &b[i]);
	}
	
	perm_array = fatoracao (n, A);
	
	x = substituicao (n, A, perm_array, b);	
	
	vetimprime_d(n, x, "%lf");
	
	matlibera(n, A);
}











