#include <stdio.h>
#include <stdlib.h>
#define SIZE  12

void saveBytes(const char* name, int* d, int n) {
	FILE* pf=fopen(name,"w");
	if(pf==0)		return;
	fwrite(d,sizeof(int),n,pf);
	fclose(pf);
}
void readBytes(const char* name) {
	FILE* pf=fopen(name,"r");
	if(pf==0) 		return;
	
	int num;
	while(1) {
		if(fread(&num,sizeof(int),1,pf)==0) break;
		printf("%d  ",num);
	}
	fclose(pf);
}
void saveText(const char* name, int* d, int n) {
	FILE* pf=fopen(name,"w");
	if(pf==0)			return;
	
	int i=0;
	for(; i<n; ++i) 	fprintf(pf,"%d ",d[i]);
	fclose(pf);
}
void readText(const char* name) {
	FILE* pf=fopen(name, "r");
	if (pf==0) 		return;
	
	int num;
	char buf[256];
	while(fscanf_s(pf,"%s", buf, 255)>0) {
		//printf("%s ", buf);
		num = atoi(buf);
		if(num!=0)	printf("%d ", num);
	}
	fclose(pf);	
}
void main(int argc, char *argv[]) {
	int dat[SIZE]={4,1,4,9,3,15,6,7};
	
	//saveBytes("data.bts",dat,SIZE);
	//readBytes("data.bts");
	
	//saveText ("data.txt",dat,SIZE);
	readText ("data.txt");
}
