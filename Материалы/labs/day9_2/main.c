#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int   len(const char* s);
char* upper(char* s);
char* summa(char* s1, int n, const char* s2);

void main(int argc, char *argv[]) {
	char* s1 = "Help Alex";
	char s2[]={'a','b','c','\0'};
	char s3[32]="Hello!+ 12ef";
	
	//printf("%s %s\n",s1,s2);
	//printf("%d %d\n",len(s1), len(s2));
	
	//printf("%s\n",upper(s3));
	printf("%s\n",summa(s3,32,".end."));
}
char* summa(char* s1, int n, const char* s2) {
	if(s1==0 || s2==0)	return s1;
	if(n<len(s1)+len(s2)+1) return s1;
	
	int i=0,n1=len(s1),n2=len(s2);
	
	for(i=0; i<=n2; ++i) {
		s1[i+n1]=s2[i];
	}
	return s1;
}
char* upper(char* s) {
    int i=0;
    for( ; i<len(s); ++i) {
        if(s[i]>='a' && s[i]<='z') s[i]-=32;		
    }
	return s;	
}
int len(const char* s) {
    int i=0;
    while(*s++) i++;
 	return i;	
}




