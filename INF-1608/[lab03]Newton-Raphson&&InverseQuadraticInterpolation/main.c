#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raiz.h"

double f (double x){
	return cos(x) - x*x*x + x	;
}

double fl (double x){
	return sin(x) - 3.0*x*x + 1.0;
}

int main(){
	double r;
	int nr;
	
	//nr = NR (3, 3, f, fl, &r);
	nr = IQI (-0.4, 0.0, 1.0, 6, f, &r);
	printf(".. %lf .. %d.. ", r, nr);

}
