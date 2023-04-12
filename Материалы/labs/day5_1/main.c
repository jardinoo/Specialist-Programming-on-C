#include <stdio.h>
#define SIZE  20
#define SIZET 10

int main(int argc, char *argv[]) {
	double dat[25]={1,2,3};
	double d2 [25]={0.0};
	double d3 [SIZE]={1,2,3,4,5, [SIZE/2]=17,18,19 };
	
	int num=15;
	double d4[num];
	 
	for(int i=0;i<SIZE;++i) printf("%g ",d3[i]);
	
	double d5[SIZET]={3,11,5,7,-9,3,2,1};
	double min=d5[0], max=d5[0], sum=0;
	//min,max,sum
	for(int i=0; i<SIZET; ++i) {
		sum += d5[i];
		if(d5[i]<min)	min=d5[i];
		if(d5[i]>max) 	max=d5[i];
	}

	printf("\n%g  %g  %g",min,max,sum); 
	return 0;
}



