#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]) {
	//simple numbers 
	int i, num=31;
	
	for(i=2; i<num; ++i) {
		if(num%i==0) break;	
	}
	if(i==num) printf("%d  ",num);
	
	//

	
	//return;
}
