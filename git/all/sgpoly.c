#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* getcoef(int nval, char** strings);
void printpoly(double coeff[], int len, double res);
double eval(double coeff[], int len, double x);
double poly(double a, double b, double c, double x);

int main(int argc, char** argv) {
    double* vect = getcoef(argc, argv);
    int size = argc-1;
    double i;
    for(i = 0; i < 3.0; i+=0.1) {
        printf("x = %lg, y = %lg\n", i, eval(vect, size, i));
    }
}

double eval(double coeff[], int len, double x) {
	int i = 0, j = 0;
	double retval = 0;
	for(i = len-1, j = 0; i >= 0; i--, j++)
		retval += coeff[j] * pow(x, i);
	return retval;
}

double* getcoef(int nval, char** strings) {
	int i;
	double* retvect = malloc(sizeof(double) * (nval-1));
	for(i = 0; i < (nval-1); i++) {
		retvect[i] = strtod(strings[i+1], NULL);
	}
	return retvect;
} 

void printpoly(double coeff[], int len, double res) {
	int i = 0, j = 0;
	for(i = len-1, j = 0; i >= 0; i--, j++)
		if(coeff[j] != 0 && i != 0)
			if(coeff[j] != 1 && coeff[j] != -1)
				printf("%+lgx^%d ", coeff[j], i);
			else if(coeff[j] == 1)
				printf("+x^%d ", i);
			else
				printf("-x^%d ", i);
		else if(coeff[j] != 0)
			printf("%+lg", coeff[j]);
	printf("= %lg", res);
}