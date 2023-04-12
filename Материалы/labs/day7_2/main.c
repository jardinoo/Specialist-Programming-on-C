#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int a=5;
	double d=1.73;
	
	int* pi=&a;
	
	printf("%X  %d\n",&a,pi);
	*pi=27;		// a=27
	printf("%d  %d\n", a, *pi);
	printf("%d\n",pi+1);
	
	double*pd=0;
	pd=&d;
	if(pd!=0) *pd=d;

	return 0;
}
