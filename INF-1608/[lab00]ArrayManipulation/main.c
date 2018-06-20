#include <stdlib.h>
#include <stdio.h>

void main(){
	double* w = vetcria(3);

	double** A = matcria(3, 3);
	double** AA = matcria(3, 3);
	double** B = matcria(3, 2);
	double** C = matcria(3, 2);
	double** D = matcria(3, 3);


	//MATRIZ 2X3
	A[0][0] = 1; A[0][1] = 3; A[0][2] = 5;
	A[1][0] = 9; A[1][1] = 8; A[1][2] = 2;

	//MATRIZ 3X2
	AA[0][0] = 1; AA[0][1] = 8;
	AA[1][0] = 0; AA[1][1] = 9;
	AA[2][0] = 2; AA[2][1] = 4;

	multmm(3, 2, 3, AA, A, D);

	matimprime(3, 3, D, "%lf");

	B[0][0] = 2; B[0][1] = 1; 
	B[1][0] = 4; B[1][1] = 0;
	B[2][0] = 3; B[2][1] = 2;

	matlibera(3, A);
	matlibera(3, AA);
	matlibera(3, B);
	matlibera(3, C);
	matlibera(3, D);
	vetlibera(w);
}