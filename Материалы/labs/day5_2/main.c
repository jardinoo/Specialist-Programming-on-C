#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char *argv[]) {
	int i,j;
	int matr[][4] = { 	{ 2, 4, 6, 1}, 
						{13,21,11,17} 	};
						
	for(i=0;i<2;++i) {
		for(j=0;j<4;++j)  printf("%4d",matr[i][j]);
		printf("\n");
	}
	
	// data
	int dat[SIZE];
	srand(time(0));
	for(i=0; i<SIZE; ++i)	dat[i]=rand();	
	
	// bsort
	for(i=1; i<SIZE; ++i) {
		for(j=0; j<SIZE-1; ++j)
			if(dat[j]>dat[j+1])  {
				int tmp=dat[j];
				dat[j]=dat[j+1];
				dat[j+1]=tmp;
			}
	}
	// print
	printf("\n");
	for(i=0; i<SIZE; ++i)	printf("%6d",dat[i]);
	
	return 0;
}
