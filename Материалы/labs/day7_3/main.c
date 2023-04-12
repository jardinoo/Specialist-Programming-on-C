#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	double dat[5]={1,2,3,4,5};
	printf("%X  %X\n", &dat[0], dat);
	
	//dat[2]  *(dat+2)  *(2+dat)   2[dat]
	int i=0;
	for(;i<5;++i)  printf("%g  ",i[dat]);
	printf("\n");
	
	double*p=dat;
	for(i=0;i<5;++i)  printf("%g  ",*p++);
	
	double d2[2][5] = {0};
	double* p1 [5];		//p1-массив из 5-и указателей на double
	double (*p2) [5];	//p2-указатель на массив из 5-и double
	p2=d2;
	
	float t=5.67F;
	float*pf=&t;
	void *pv=&t;
	double*pd=(double*)&t;	//!
	
	printf("\n%g",*pf);
	printf("\n%g",*(float*)pd);	
	printf("\n%g",*(float*)pv);
	return 0;
}



