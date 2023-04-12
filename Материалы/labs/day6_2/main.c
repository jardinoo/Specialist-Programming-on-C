#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
double  mymax (double d[], int n);
double* mystat(double d[], int n);
double  mymax2(double d[], int row, int col);

void main(int argc, char *argv[]) {
	double d[SIZE]={4.1,5,7,0.94,1,-6,3,2,8,1};
	double min,max;
	max=mymax(d,SIZE);
	mystat(d,SIZE);	
	//printf("max=%g\n",max);
	
	double d2[2][3]={ {21,27,-3}, {5,7,12} };
	//max=mymax2(d2,2,3);
	//printf("max=%g\n",max);
}
double* mystat(double d[], int n) {
	int i=1;
	double max=d[0], min=d[0];
	
	for( ; i<n; ++i) {
		if(d[i] > max)	max=d[i];
		if(d[i] < min)	min=d[i];	
	}
	double res[2]={min, max};
	return res;		//
}
double mymax2(double d[], int row, int col) {
	double a=d[0];
	int i=1,n=row*col;
	
	for( ; i<n; ++i)
		if(d[i] > a)	a=d[i];
	return a;
}
double mymax(double d[], int n) {
	double a = d[0];
	int i;
	for(i=1; i<n; ++i) {
		if (d[i] > a) 	a=d[i];
	}
	return a;
}


