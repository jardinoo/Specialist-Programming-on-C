#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int max;
	int a=13,b=7,num=1;
	
	if(a>b) { 
		double count=0, num=5.1;
		
		printf("a>"); 
		max=a; 
		//printf("%g",num);
	}
	else	{ printf("b>"); max=b; }
	
	// ++count;
	if(num==0) {}	// 7
	if(0==num) {}	//		Best
	if(!num)   {}	// 4
	
	max = (a>b)? a: b;
	
	return 0;
}
