#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]) {
	addItem("C++");
	addItem("Java");
	addItem("Scala");
	
	//printf("count=%d\n",getCount());
	//printList();
	//delItem(); delItem(); delItem(); delItem();
	
	//qsort();
	
	addItem("Fortran");
	printList();
	int ind=findItem("fortran");
	printf("index=%d\n",ind);
	
	return 0;
}
