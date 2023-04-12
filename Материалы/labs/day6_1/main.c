#include <stdio.h>
#include <stdlib.h>
void   swap(int*pa, int*pb);
double powN(double d, int n);

void main(int argc, char *argv[]) {
	//printf("%g\n",powN(2,3));
	
	int x=5,y=2;
	swap(&x, &x);
	printf("x=%d  y=%d\n",x,y);
}
void swap(int*pa, int*pb) {
	if(pa==pb)		return;
	int tmp=*pa;		//tmp=x
	*pa=*pb;			//x=y;
	*pb=tmp;			//y=tmp
}


double powN(double d, int n) {
	double res=1; 
	int i=1;
	for( ;i<=n; ++i) res*=d;
	return res;
}


