#include <stdio.h> 
#include "stdlib.h"

#define NAME
#define PI 3.1415
#define PF printf
#define BEGIN {
#define END }
#define INTEGER int
#define START int main(INTEGER argc, char *argv[])
#define A START BEGIN\
	INTEGER num=0, summa=0;\
	PF("vvedite chislo:");\
 	scanf ("%d",&num);\
	INTEGER n=num;\
	if(num<0) num= -num;
#define B 	while(num>0) BEGIN\
		summa += num%10;\
		num /= 10;\
	END
#define C 	PF("summa %d = %d\n",n, summa);\
	return 0;\
END
