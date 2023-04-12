#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

void putInt   (int n)    { printf("%d(int)  ",n); }
void putDouble(double d) { printf("%g(dbl)  ",d); }

#define put(X) \
	_Generic((X), \
		int: putInt, \
		double: putDouble)((X)) 

int main(int argc, char *argv[]) {
	int a=5,c=17;
	double b=11.3;
	sin(2.1f);
	
	put(a);
	put(b);
	put(c);	
	
	return 0;
}
