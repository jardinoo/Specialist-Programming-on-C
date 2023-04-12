#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int a,b,c,max=0;
 A:	printf("Input a b c:");
	scanf("%d %d %d",&a,&b,&c);
	
	max = (a>b)? a>c?a:c : b>c?b:c ;
	
//	if(a>b)	 { max=a; }
//	else	 { max=b; }
//	if(c>max){ max=c; }	
	
	printf("max=%d\n",max);
//	goto A;
	
	int n=4;
	switch(n) {
		default:printf("??"); break;
		case 5: printf("5 "); break; 
		case 4: printf("4 "); break; 
		case 3: printf("3 "); break; 
		case 2: printf("2 "); break; 
	}
	return 0;
}



