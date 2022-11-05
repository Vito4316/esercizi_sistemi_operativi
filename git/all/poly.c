#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define LOG(x) printf("%s: %lg\n", #x, (double) (x))

#define ERROR 0.0001
 
double* getcoef(int nval, char** strings) {
	int i;
	double* retvect = malloc(sizeof(double) * (nval - 1));
	for(i = 0; i < nval-1; i++) {
		retvect[i] = strtod(strings[i+1], NULL);
	}
	return retvect;
} 
 
int inbetween(double val, double a, double b) {
	return (b > val && val > a) || (a > val && val > b); }
double eval(double coeff[], int len, double x);
void printpoly(double coeff[], int len, double res);
double searchrange(double coeff[], int len, double res);
double findvalue(double coeff[], int len, double res, double left, double right);
double poly(double coeff[], double res, int len);

int main(int argc, char** argv) {
	double* values = getcoef(argc, argv);
	int values_size = argc-2;
	
	/*values[values_size] contains res*/
	printpoly(values, values_size, values[values_size]);
	printf("x = %lg\n", poly(values, values[values_size], values_size));
	
	free(values);
	return 0;
}

double eval(double coeff[], int len, double x) {
	int i = 0, j = 0;
	double retval = 0;
	for(i = len-1, j = 0; i >= 0; i--, j++)
		retval += coeff[j] * pow(x, i);
	return retval;
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
	printf("= %lg\n", res);
}

double searchrange(double coeff[], int len, double res) {
	double range = 1;
	double x0 = eval(coeff, len, 0);
	#ifdef DEBUG
	LOG(x0);
	#endif
	while(range < DBL_MAX / 2) {
		double temp1 = eval(coeff, len, range);
		double temp2 = eval(coeff, len, -range);
		
		#ifdef DEBUG
		LOG(range);
		LOG(temp1);
		LOG(temp2);
		#endif
		
		if(inbetween(res, temp1, x0))
			return range; 
		if(inbetween(res, temp2, x0))
			return -range;
		range *= 2;
	}
	return DBL_MAX;
}

double findvalue(double coeff[], int len, double res, double left, double right) {
	if(left > right) {
		double temp = left;
		left = right;
		right = temp;
	} 
	double lval = eval(coeff, len, left);
	double rval = eval(coeff, len, right);
	double mid = eval(coeff, len, (left+right)/2);
	
	#ifdef DEBUG
	LOG(left);
	LOG(right);
	LOG(mid);
	#endif
	
	if(mid + ERROR > res && res > mid - ERROR)
		return (left+right)/2;
	
	if(inbetween(res, mid, rval))
		return findvalue(coeff, len, res, (left+right)/2, right);
	
	if(inbetween(res, lval, mid)) 
		return findvalue(coeff, len, res, left, (left+right)/2);
		
	return DBL_MAX;
}

double poly(double coeff[], double res, int len) {
	double range = searchrange(coeff, len, res);
	if(range == DBL_MAX) return range;
	return findvalue(coeff, len, res, 0, range); 
}
