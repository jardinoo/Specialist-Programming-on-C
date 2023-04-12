#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static int   count=0;
static Item *begin=0, *end=0;

int getCount() { return count; }

int  findItem(void* s) {
	Item* pt=begin;
 	int i=0;
 	for( ; i<count; i++) {
 		if(stricmp(s,pt->p)==0)		return i;
     	pt=pt->next;
    }
	return -1;	
}
void printList() {
	Item* pt=begin;
 	int i=0;
 	for( ; i<count; i++) {
 		printf("%s\n",pt->p);
     	pt=pt->next;
 }
}
void delItem() {
	if(count==0) return;
	if(count==1) {
		free(end);
		begin=end=0;
		count--;
	}
	else {
		//Item* tmp = end->prev;
		end->prev->next=0;
		end = end->prev;
  		free(end->next);
		count--;
	}
}
void addItem(void* s) {
	Item *pi=malloc(sizeof(Item));
	//проверка
	pi->next=0;
	pi->prev=0;
	pi->p = s;	
	
	if(count==0) {
		begin=end=pi;
		count++;
	}
	else {
		end->next=pi;
		pi->prev=end;
		
		end=pi;
		count++;
	}
}



