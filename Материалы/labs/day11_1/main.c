#include <stdio.h>
#include <stdlib.h>

enum Days { mon=1, tue, wen, thu, fri };
union Test{
	unsigned char c[4];
	long  num;
	float f;	
};

typedef unsigned char uchar;

union Test2 {
	uchar c;
	struct {
		uchar b0:1;	
		uchar b1:1;
		uchar b2:1;
		uchar b3:1;
		uchar b4:1;
		uchar b5:1;
		uchar b6:1;
		uchar b7:1;
	} byte;
};

int main(int argc, char *argv[]) {
	enum Days d=tue;
	switch(d) {
		case mon:    break;
		case tue:    break;
	}
	printf("mon=%d  %d\n",mon,d);
	
	union Test t1;
	printf("size=%d\n",sizeof(t1));
	
	t1.c[0]=78;	t1.c[1]=210; t1.c[2]=150; t1.c[3]=55;
	
//	long colour=0;
//	colour=0x37;	colour=colour<<8;
//	colour|=0x96;	colour=colour<<8;
//	colour|=0xd2;	colour=colour<<8;
//	colour|=0x4e;
	printf("colour=%x\n",t1.num);
	
	union Test2 num;
	num.c=0;
	printf("size=%d\n",sizeof(num));
	num.byte.b0=1;
	num.byte.b2=1;
	num.byte.b3=1;
	printf("%d\n",num.c);
	
	return 0;
}








