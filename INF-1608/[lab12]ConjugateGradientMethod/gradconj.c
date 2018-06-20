#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gradconj.h"
#include "vetmat.h"
#define format "%lf "

static void copia_vetor (int n, double* dest, double* source){
	int i;

	for(i = 0; i < n; i++)
		dest[i] = source[i];
}

static void mutlv_tv (int n, double* x, double* t, double** xt_x){
	int i, j;

	for (i = 0; i<n; i++){
		for (j = 0; j < n; j++){
			xt_x[i][j] = x[i] * t[j];
		}
	}
}


static double* cria_vet_differenca (int n, double* first, double* second){	// results in v[i] - w[i]
	double *x = vetcria(n);
	for (int i = 0; i < n; i++)
		x[i] = first[i] - second[i];
	
	return x;
}

int GradConj (int n, double** A, double* b, double* x, double tol){
	
	//CONTADORES//
	int i, j, k;

	//VETORES//
	double* A_x = vetcria(n);
	double* d = vetcria(n);
	double* A_d = vetcria(n);
	double* residuo;

	//ESCALARES//
	double norma2r = 1;
	double beta;

	multmv(n,n, A, x, A_x);						//A*x
	residuo = cria_vet_differenca(n, b, A_x);	//r = b - A*x
	copia_vetor(n, d, residuo);					//d <= r
	double rt_r_k = escalar(n, residuo, residuo);

	for (k=0; ;k++){	//iterações
		norma2r = norma2(n, residuo);//CALCULO DE ||rk||2

		if (norma2(n, residuo)< tol) break;	// SE ||rk||2 < TOL, PARA 

		multmv(n, n, A, d, A_d); 					// A x d

		//double rt_r_k = escalar(n, residuo, residuo);	//rk_t * rk
		double alfa = rt_r_k/escalar(n, residuo, A_d);	//dk_t * A * dk

		for (i = 0; i < n; i ++){
			x[i] += alfa*d[i];			//xk+1 = xk + alfak * dk
			residuo[i] -= alfa*A_d[i];	//rk+1 = rk - alfak * A * dk
		}

		double rt_r_k1 = escalar(n, residuo, residuo);
		beta = rt_r_k1/rt_r_k;

		for (i = 0; i < n; i ++){
			d[i] = residuo[i] + beta*d[i];
		}
		rt_r_k = rt_r_k1; //não preciso calcular de novo o rk_t * rk, pois o rk+1 dessa iteração é o rk da próxima.
	}

	vetlibera(A_x);
	vetlibera(d);
	vetlibera(A_d);
	vetlibera(residuo);

	return k;
}
/*
int GradConjJacobi (int n, double** A, double* b, double* x, double tol){

	//CONTADORES//
	int i, j, k;

	//VETORES//
	double* A_x = vetcria(n);
	double* d = vetcria(n);
	double* z = vetcria(n);
	double* A_d = vetcria(n);
	double* residuo;

	//ESCALARES//
	double norma2r = 1;
	double beta;

	multmv(n,n, A, x, A_x);						//A*x
	residuo = cria_vet_differenca(n, b, A_x);	//r = b - A*x
		printf("oi");

	for (i = 0; i < n; i++){
		d[i] = 1.0/A[i][i] * residuo[i];				// d[i] = M⁻¹*r0
	}
	copia_vetor(n, z, d);						// z <= d
	double rt_r_k = escalar(n, residuo, residuo);
	double rtk1_zk1 = escalar(n, residuo, z);

	for (k=0; ;k++){	//iterações
		norma2r = norma2(n, residuo);//CALCULO DE ||rk||2
		double rt_z = escalar(n, residuo, z);

		if (norma2(n, residuo)< tol) break;	// SE ||rk||2 < TOL, PARA 

		multmv(n, n, A, d, A_d); 					// A x d

		//double rt_r_k = escalar(n, residuo, residuo);	//rk_t * rk
		double alfa = rt_r_k/escalar(n, residuo, A_d);	//dk_t * A * dkx

		for (i = 0; i < n; i ++){
			x[i] += alfa*d[i];			//xk+1 = xk + alfak * dk
			residuo[i] -= alfa*A_d[i];	//rk+1 = rk - alfak * A * dk
			z[i] = 1.0/A[i][i]*residuo[i];
		}

		
		beta = rtk1_zk1/rt_z;

		
		for (i = 0; i < n; i ++){

			d[i] = residuo[i] + beta*d[i];

		}
		
		rt_r_k = rtk1_zk1; //não preciso calcular de novo o rk_t * rk, pois o rk+1 dessa iteração é o rk da próxima.
	}

	vetlibera(A_x);
	vetlibera(d);
	vetlibera(z);
	vetlibera(A_d);
	vetlibera(residuo);

	return k;


}
*/



int GradConjJacobi (int n, double** A, double* b, double* x, double tol){
	
	//CONTADORES//
	int i, j, k;

	//VETORES//
	double* A_x = vetcria(n);
	double* d = vetcria(n);
	double* A_d = vetcria(n);
	double* z = vetcria(n);
	double* residuo;

	//ESCALARES//
	double norma2r = 1;
	double beta;

	multmv(n,n, A, x, A_x);						//A*x
	residuo = cria_vet_differenca(n, b, A_x);	//r = b - A*x

	for (i = 0; i < n; i++){
		z[i] = (1.0/A[i][i])*residuo[i];
	}

	//printf("vetor z");
	//vetimprime(n,z,"%lf ");

	copia_vetor(n, d, z);					//d <= r
	double rt_z_k = escalar(n, residuo, z);

	for (k=0; norma2r > tol;k++){	//iterações
		norma2r = norma2(n, residuo);//CALCULO DE ||rk||2

		multmv(n, n, A, d, A_d); 					// A x d

		//double rt_r_k = escalar(n, residuo, residuo);	//rk_t * rk
		double alfa = rt_z_k/escalar(n, residuo, A_d);	//dk_t * A * dk

		for (i = 0; i < n; i ++){
			x[i] += alfa*d[i];			//xk+1 = xk + alfak * dk
			residuo[i] -= alfa*A_d[i];	//rk+1 = rk - alfak * A * dk
			z[i] = 1.0/A[i][i] * residuo[i];
		}

		double rt_z_k1 = escalar(n, residuo, z);
		beta = rt_z_k1/rt_z_k;

		for (i = 0; i < n; i ++){
			d[i] = z[i] + beta*d[i];
		}
		rt_z_k = rt_z_k1; //não preciso calcular de novo o rk_t * rk, pois o rk+1 dessa iteração é o rk da próxima.
	}

	vetlibera(A_x);
	vetlibera(d);
	vetlibera(z);
	vetlibera(A_d);
	vetlibera(residuo);

	return k;
}