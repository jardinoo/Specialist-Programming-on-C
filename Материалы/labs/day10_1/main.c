#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  NROW  5

int cmp1(const void*p1, const void*p2) {
	char*s1 = *(char**)p1;
	char*s2 = *(char**)p2;
	return strcmp(s1,s2);
}
int main(int argc, char *argv[]) {
	int i=0;
	// for(; i<argc; ++i)	puts(argv[i]);
	char buf[256];
	char*s[NROW]={0};
	// ввод строк
	for(i=0; i<NROW; ++i) {
		scanf("%s",buf);
		s[i]=malloc(strlen(buf)+1);
		if(s[i]==0)	{ puts("No memmory!"); return -17283; }
		strcpy(s[i],buf);
	}
	// сортировка
	qsort(s,NROW,sizeof(char*),cmp1);
	printf("\n");
	for(i=0; i<NROW; ++i)	puts(s[i]);	
	// free()
	return 0;
}
