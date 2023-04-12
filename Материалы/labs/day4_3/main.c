#include <stdio.h>

#define TEST
#define cube(x)  ((x)*(x)*(x))
#define SWAPI(x,y) do{int x##y =x; x=y; y= x##y;}while(0)

int main(int argc, char *argv[]) {
	int count=2, n=2;
	
	printf("%d\n",27/cube(count+1));
	cube(++n);
	if(count>0)		printf("%d\n",n);
	
	#ifdef TEST
		printf("test print 1\n");
	#endif
	
	int a=5,b=7;
	n=2;
	if(count>0)		SWAPI(n,b);
	else {}
	
	printf("n=%d  b=%d\n",n,b);
	
	#ifdef TEST
		printf("test print 2 line=%d %s\n",__LINE__,__func__);
	#endif
	
	return 0;
}










