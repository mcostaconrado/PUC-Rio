#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <malloc.h>
#include "mmq.h"
#include "vetmat.h"
#include "sistlinear.h"

/*INSTRUÇÕES DE COMPILAÇÃO APÓS A MAIN()*/

int main(){
	int resposta = -1;
	int m, n;
	int i, j;
	double k = 0.0;
	double* resultado;
	
	scanf("%d", &resposta);
	
	
	if (resposta == 1){		//resolver os sistemas
		scanf("%d %d", &m, &n);
	
		double** A = matcria(m, n);
		double* b = vetcria(m);
	
		for (i=0; i<m; i++){
			for(j=0; j<n; j++){
				scanf("%lf ", &A[i][j]);
			}
		}
	
		for (i = 0; i < m; i++){
			scanf("%lf", &b[i]);
		}
	
		printf("\nMatriz A:\n");
		matimprime(m, n, A, "%lf");
	
		printf("\nVetor b:\n");
		vetimprime(m, b, "%lf ");
	
		resultado = mmq (m, n, A, b);
	
		printf("\nResultado aproximado do sistema:\n");
		vetimprime(n, resultado, "%lf ");
	
		printf("\nNorma2 do erro: %lf.\n\n", mmqNorma2 (m, n, A, b, resultado));
		
		matlibera(m, A);
		vetlibera(b);
		
	}
	
	else if (resposta == 0){	//resolver a concentracao
		scanf("%d", &n);
		double* t = vetcria(n);
		double* c = vetcria(n);
		double pa, pb;
		double norma;
		
		for (i = 0; i < n; i++){
			scanf("%lf %lf", &t[i], &c[i]);
		}
		
		norma = concentracao (n, t, c, &pa, &pb);
		
		printf("\nCoeficiente a: %lf.\nCoeficiente b: %lf.\nNorma2 do erro: %lf.\n\n", pa, pb, norma);
		vetlibera(t);
		vetlibera(c);
		
		printf("\nt [s]\tc [ng/ml]\n\n");
		while(k <= 16.0){
			printf("%.1lf\t%.5lf\n", k, pa*k*exp(pb * k));
			k += 0.1;
		}
	}


	return 0;
}

/* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

COMPILAÇÃO E EXECUÇÃO:

gcc -o mmq mmq.c sistlinear.c vetmat.c main.c -lm
./mmq < input?.txt

onde ? é o número do arquivo de input desejado.

o primeiro numero do arquivo é:
						-1 (para resolver o sistema apenas)
						-0 (para resolver o problema de concentração)

input1.txt:

1


5 3

3 -1 2
4 1 0
-3 2 1
1 1 5
-2 0 3

10
10
-5
15
0	


input2.txt:

1


5 4	

4 2 3 0
-2 3 -1 1
1 3 -4 2
1 0 1 -1
3 1 3 -2

10
0
2
0
5


input3.txt

0

8	

1	8.0
2	12.3
3	15.5
4	16.8
5	17.1
6	15.8
7	15.2
8	14.0

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
