#include <stdio.h>
#include <stdlib.h>

struct Date { int year,month,day; };
struct tagBook {
	char title[64];	
	int  pages;
	struct Date dat;
};
typedef struct tagBook Book;
typedef unsigned long long ullong;

struct 	Test    {
  char 	a; 	
  char 	b : 5 ; 		
  char  c : 1 ; 	
  char  d : 2 ; 		
} ; 

void inputBook(Book* p) {
	printf("Input yyyy-mm-dd: ");
	scanf ("%d-%d-%d",&p->dat.year,&p->dat.month,&p->dat.day);
	
	printf("Pages=");
	scanf ("%d",&p->pages); 
	fflush(stdin);
	
	printf("Title:");
	gets(p->title);		
}
void printBook(Book b) {
	printf("%s (%d) %d-%d-%d\n",b.title,b.pages,
								b.dat.year,b.dat.month,b.dat.day);
}
int main(int argc, char *argv[]) {
	Book b1,b2={"Modern C", .dat={2011, .day=23}};
	//b1=b2;
	//inputBook(&b1);
	//printBook(b1);
	//printBook(b2);
	printf("size=%d\n",sizeof(struct Test));
	
	return 0;
}
