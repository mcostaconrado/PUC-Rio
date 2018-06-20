#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include "sistlinear.h"

static double* vetcria_d (int n){
	double *p = (double*)malloc(sizeof(double)*n);
	if (p != NULL)
		return p;
	exit(1);
}

static int* vetcria_i (int n){
	int *p = (int*)malloc(sizeof(int)*n);
	if (p != NULL)
		return p;
	exit(1);
}

static void vetlibera_d (double* v){
	free (v);
}

static void vetlibera_i (int* v){
	free (v);
}

static double** matcria (int m, int n){
	int i;
	double** mat = (double**) malloc(sizeof(double*)*m);
	
	for (i = 0; i < m; i++)
		mat[i] = (double*)malloc(sizeof(double)*n);
	return mat;
}

static void matlibera(int m, double** A) {
	int i;

	for (i = 0; i < m; i++)
		free(A[i]);

	free(A);
}

static void permutation(double**A, double** mtx_factors, int* perm_array, int j, int n, int indice_max){
	int k;													// k is a variable to go through the line (#indice_max and #j) by its columns
	double* aux = vetcria_d(n);			// we have to switch lines #indice_max and #j for each other.
	int a;
	
	for(k = 0; k < n; k++){					// so, k is going from 0 to k, so we can change all the columns of a line
		aux[k] = A[j][k];							// auxiliar array receives value of line #j
		A[j][k] = A[indice_max][k];		// line #j receives line #indice_max value
		A[indice_max][k] = aux[k];		// line #indice_max receives line #j value
	}
	
	for (k = 0; k<n; k++){
		aux[k] = mtx_factors[j][k];							// auxiliar array receives value of line #j
		mtx_factors[j][k] = mtx_factors[indice_max][k];		// line #j receives line #indice_max value
		mtx_factors[indice_max][k] = aux[k];		// line #indice_max receives line #j value
	}
																	// at this point, line #j is line #indice_max and vice versa
	
	vetlibera_d(aux);								// after changing values, the auxiliar array has no function anymore

	a = perm_array[indice_max];			// Here, we change the values of perm_array
	perm_array[indice_max] = perm_array[j];	
	perm_array[j] = a;

}

static void gaussianElimination (int n, double** A, int* perm_array, double** mtx_factors){
	int i, j;
	int indice_max;
	
	for (j = 0; j < n-1; j++){			// j is the jth diagonal
		double max = fabs(A[j][j]);						// max receives the jth diagonal value
		indice_max = j;								// indice_max receives j value
		
		/*--------- START OF PIVOTING ---------*/		
		
		for (i = j+1; i < n; i++){		// i is the number of the line. Here i am seeking for the max value of the jth column
			
			if (fabs(A[i][j]) > max){		// if another value is greater than the diagonal value...
				
				max = A[i][j]; 						// max receives the diagonal value...
				indice_max = i;						// and indice_max receives i (line) value
			}
		}

		if (indice_max != j){ // PERMUTATION							// if the max value isn't the diagonal value...
			permutation(A, mtx_factors, perm_array, j, n, indice_max);	// we have to perfom a permutation
		}
		
		/*--------- END OF PIVOTING ---------*/
		
		for (i = j+1; i < n; i++){
			int columns;
			double factor = A[i][j]/A[j][j];
			mtx_factors[i][j] = factor;
			
			for (columns = 0; columns < n; columns++){
				A[i][columns] = A[i][columns] - factor*A[j][columns];
				if (fabs(A[i][j]) <= 10e-16) A[i][j] = 0.0;		// fixes the -0.00000 'bug'  :)
			}
		}	
	}
	
	for (i = 1; i < n; i++){
		for (j = 0; j < i; j++){
			A[i][j] = mtx_factors[i][j];
		}
	}
}

static void bottom_up(int n, double** A, double* b, double* solution){
	int i, j;
	double sum = 0;
	
	solution[n-1] = b[n-1]/A[n-1][n-1]; 
	
	if (n == 1) return;
	
	for (i = n-2; i >= 0; i--){
			for(j = n-1; j > i; j--){
				sum = sum + A[i][j] * solution[j];
			}
			solution[i] = (b[i] - sum)/A[i][i];
			sum = 0;
	}
}

static void top_down (int n, double** A, double*b, double* solution){
	int i, j;
	double sum = 0;
	
	solution[0] = b[0];
	
	if (n == 1) return;
	
	for (i = 1; i < n; i++){
		for (j = 0; j < i; j++){
			sum += A[i][j]*solution[j];
		}
		solution[i] = b[i] - sum;
		sum = 0;
	}
}

int* fatoracao (int n, double** A){
	int i, j;
	int* perm_array = vetcria_i(n);
	double** mtx_factors = matcria (n, n);
	
	for (i = 0; i<n; i++) perm_array[i] = i;
	
	gaussianElimination(n, A, perm_array, mtx_factors);
		
	matlibera(n, mtx_factors);
	
	return perm_array;
}

double* substituicao (int n, double** A, int* p, double* b){
	double* b_aux = vetcria_d(n);
	double* y = vetcria_d(n);
	double* x = vetcria_d(n);
	int i;
	
	for (i = 0; i<n; i++){
		double aux = b[p[i]];
		b_aux[i] = aux;
	}
	
	top_down(n, A, b_aux, y);
	bottom_up(n, A, y, x);
	
	vetlibera_d(y);
	vetlibera_d(b_aux);
	return x;

}
