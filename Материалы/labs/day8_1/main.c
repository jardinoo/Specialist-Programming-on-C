#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// double cos(double x);
#define SIZE 25

int func1(const void* p1, const void* p2) {
	int res=0;
	int a=*(int*)p1;
	int b=*(int*)p2;
	if(a>b) res=1;
	else if(a<b) res=-1;
	return res;	
}
int func2(const void* p1, const void* p2) {
	return -func1(p1,p2);	
}
int func3(const void* p1, const void* p2) {
	int res=0;
	int a=*(int*)p1;
	int b=*(int*)p2;
	
	if(a%2==0 && b%2!=0) 	res=-1;
	if(a%2!=0 && b%2==0)	res=+1;
	if(a%2==0 && b%2==0)    res=a-b;
	if(a%2!=0 && b%2!=0)    res=b-a;
	
	return res;	
}
void main(int argc, char *argv[]) {
	
	printf("%g\n",cos(3.1415));
	printf("%X  %X\n",&cos,cos);
	
	double (*pf)(double x);
	pf=cos;
	printf("%g\n",(*pf)(3.1415));
	
	int i, d[SIZE];
	for(i=0; i<SIZE; ++i)	d[i]=rand()%100;
	
	qsort(d,SIZE,sizeof(int),func3);
	for(i=0; i<SIZE; ++i)	printf("%d  ",d[i]);
}






