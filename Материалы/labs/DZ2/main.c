#include <stdio.h>
#include <stdlib.h>

void minMax(int* d, int n, int* pa, int*pb) {
	int i,min,max;
	min=max=d[0];		//min=max=*d	d[0]  *(d+0)   *d

	for(i=1; i<n; ++i) {
		if(d[i] > max)		max=d[i];
		if(d[i] < min)		min=d[i];
	}
//	printf("%d  %d",min,max);
//	int res[2]={min,max};
	if(pa!=0)	*pa=min;
	if(pb!=0)   *pb=max;
}
int* minMax2(int* d, int n) {
	int i,min,max;
	min=max=d[0];		//min=max=*d	d[0]  *(d+0)   *d

	for(i=1; i<n; ++i) {
		if(d[i] > max)		max=d[i];
		if(d[i] < min)		min=d[i];
	}
	int*p=malloc(2*sizeof(int));			//8 2*4 2*sizeof(int)
	if(p==0)	return;
	p[0]=min;  p[1]=max;
	return p;
}
void main(int argc, char *argv[]) {
	int d[7]={13,0,5,18,5,2,-4};
	int a,b;
	//minMax(d,7,&a,&b);
	int*res=minMax2(d,7);
	printf("%d  %d",res[0],res[1]);
	res=minMax2(d,17);
	
	free(res);
	res=0;
}



