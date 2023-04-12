#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i;
	
//	printf("%d - enter",'\n');
	
	for(i=0; i<256; ++i) {
		switch(i) {
			case '\0': printf("%4d - \\0  \n",i); break;
			case '\n': printf("%4d - enter\n",i); break;
			case '\a': printf("%4d - sound\n",i); break;
			case '\t': printf("%4d - \\t  \n",i); break;
			
			default:   printf("%4d - %c\n",i,i); break;
		}
		//if(i=='\n')	printf("%4d - enter\n",i);
		//else 		printf("%4d - %c\n",i,i);
	}
	
//	for( i=1; i<=100; i++) {
//		printf("%4d",i);
//		if(i%10 == 0)	printf("\n");
//	}
 	return 0;
}

