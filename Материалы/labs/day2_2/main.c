#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int a=1,b=3,c=2;
	a = b++;				// b=b+1
	printf("%d %d\n",a,b);
	b=7;
	a = b/c;			
	printf("%d %d\n",a,b%c);
	
	printf("%d\n",!-45);
	printf("%hu\n",8>>2);
	
	//day 3
	printf("size=%d\n",sizeof(2/4.1));
	printf("size=%d\n",sizeof(long long int));
	printf("size=%d\n",sizeof(char));
	
	printf("%g\n",(double)b/c);
	
	int count;
	2+(count=printf("Hello"));
	a+b;
	return 0;
}




