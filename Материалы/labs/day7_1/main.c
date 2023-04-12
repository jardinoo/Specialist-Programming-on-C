#include <stdio.h>
#include <stdlib.h>
static int count=1;

long long factorial(int n) {
	long long res=1;
	if(n==1) return 1;
	res=n*factorial(n-1);
	return res;
}
testStatic() {
	int a=0;
 static	int b=0;
	
	++a;	printf("a=%d\n",a);
	++b;	printf("b=%d\n",b);
}
int main(int argc, char *argv[]) {
	
	printf("%3d-%lld\n",3,factorial(3));
	testStatic();
	testStatic();
	testStatic();

	return 0;
}





