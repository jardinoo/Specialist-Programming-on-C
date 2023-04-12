#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int summa(int n, ...) {
	int i, sum=0;
	va_list p;
	va_start(p,n);
	
	for(i=1; i<=n; ++i) 	sum += va_arg(p,int) ;
	
	va_end(p);
	return sum;
}
void main(int argc, char *argv[]) {
	int s=summa(5, 2,-3,5,2,1);
	printf("s=%d\n",s);
}
