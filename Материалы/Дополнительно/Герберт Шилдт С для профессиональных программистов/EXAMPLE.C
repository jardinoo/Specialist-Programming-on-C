     #include "stdio.h"
     #include "dos.h"
     #include "stdlib.h"

     #define BORDER 1
     #define ESC 27
     #define REV_VID 0x70
	 #define NORM_VID  7

	 #define goto_xy(x,y) _settextposition(x,y)
	 #define bioskey(x) _bios_keybrd(x)

     void save_video(),restore_video();
	 void cls(),write_video();
     void display_menu(),draw_border();

     char *fruit[] = {
      "������",
      "��������",
      "�����",
      "���������",
      "������",
      "��������"
     };

     char *color[]={
      "�������",
      "������",
      "���������",
      "�������"
     };

     char *apple_type[] = {
      "������� ���������",
      "��������",
      "����� �����",
      "���������"
     };

     main()
     {
      int i;

     cls();
     goto_xy(0,0);
     for(i=0;i<25;i++)
      printf("��� ���� ����������� ����\n");
     popup(fruit,"������",6,1,3,BORDER);
     popup(color,"����",4,5,10,BORDER);
     popup(apple_type,"����",4,10,18,BORDER);
     }

     /* ������� ���������� ���� � ������� �����
        ���������� -2, ���� ���� �� ����� ���� �������
        ���������� -1, ���� ������������ ����� ������� ESC
        � ��������� ������� ��� ���������� ����� ���������
        ������������, ������� � 0 */
     int popup(menu,keys,count,x,y,border)
     char *menu[];  /* ����� ���� */
     char *keys;    /* ������� ������� */
     int count;     /* ����� ����������� */
     int x,y;       /* ���������� ������ �������� ���� */
     int border;    /* ���� 0 �� ��� ����� */
     {
      register int i,len;
	  int endx,endy,choice;
      unsigned char *p;

      if((x>24)||(x<0)||(y>79)||(y<0)) {
       printf(" ����� �� ������� ������");
       return -2;
      }
     /* ���������� �������� */
     len=0;
     for(i=0;i<count;i++)
      if(strlen(menu[i]) > len) len=strlen(menu[i]);
     endy=len+2+y;
     endx=count+1+x;
     if((endx+1>24) || (endy+1>79)) {
       printf(" ����� �� ������� ������");
       return -2;
      }
     /* ���������� ������ ��� ����� ������ */
     p=(unsigned int *)malloc((endx-x+1)*(endy-y+1));
      if(!p) exit(1); /* �� ������ ����� ���� ���������� ������ */

     /* ���������� ����� ������ */
	 save_video(x,endx+1,y,endy+1,p);

     if(border) draw_border(x,y,endx,endy);

     /* ������������ ���� �� ����� ����� */
	 display_menu(menu,x,y,count);

     /* ������ ����� ������������ */
	 choice=get_resp(x,y,count,menu,keys);

     /* �������������� ����� ������ */
	 restore_video(x,endx+1,y,endy+1,p);
     free(p);
     return choice;
     }

     /* ������������ ���� �� ����� ����� */
     void display_menu(menu,x,y,count)
     char *menu[];
     int x,y,count;
     {
      register int i;

     for(i=0;i<count;i++,x++) {
       goto_xy(x,y);
       printf(menu[i]);
       }
     }

     is_in(s,c)
     char *s,c;
     {
      register int i;

      for(i=0; *s; i++)
         if(*s++ == c) return i+1;
      return 0;
     }

     void draw_border(startx,starty,endx,endy)
     int   startx,starty,endx,endy;
     {
      register int i;

      for(i=startx+1;i<endx;i++) {
     goto_xy(i,starty);
     putchar(179);
     goto_xy(i,endy);
     putchar(179);
     }

      for(i=starty+1;i<endy;i++) {
     goto_xy(startx,i);
     putchar(196);
     goto_xy(endx,i);
     putchar(196);
     }

     goto_xy(startx,starty); putchar(218);
     goto_xy(startx,endy  ); putchar(191);
     goto_xy(endx  ,starty); putchar(192);
     goto_xy(endx  ,endy  ); putchar(217);
     }

     /* ������ ����� ������������ */
     get_resp(x,y,count,menu,keys)
     int x,y,count;
     char *menu[];
     char *keys;
     {
      union inkey {
        char ch[2];
        int i;
      } c;
     int arrow_choice=0,key_choice;

     y++;
     /* �������� ������ ����� */
     goto_xy(x,y);
     write_video(x,y,menu[0],REV_VID);

     for(;;) {
      while(!bioskey(1)); /* ����� ������� */
      c.i=bioskey(0);

     /* ������� ����� � ��������� ����� */
     goto_xy(arrow_choice,y);
     write_video(x+arrow_choice,y,
			 menu[arrow_choice],NORM_VID);
     if(c.ch[0]) { /* ������� ������� */
	  key_choice= is_in(keys,tolower(c.ch[0]));
     if(key_choice) return key_choice-1;
     switch(c.ch[0]) {
       case '\r' : return arrow_choice;
       case ' '  : arrow_choice++;
                   break;
      case ESC   : return -1; /* ����� */
        }
     }
     else { /* ����������� ������� */
      switch(c.ch[1]) {
       case 72 : arrow_choice--; /* ������� ���� */
                 break;
       case 80 : arrow_choice++; /* ������� ����� */
                 break;

          }
       }
     if(arrow_choice==count) arrow_choice=0;
     if(arrow_choice<0) arrow_choice=count-1;
         /* ���������� ��������� ����� */
      goto_xy(x+arrow_choice,y);
      write_video(x+arrow_choice,y,menu[arrow_choice],REV_VID);
      }
     }

     /* ����� ������ � ������������ ��������� */
     void write_video(x,y,p,attrib)
     int x,y;
     char *p;
     int attrib;
     {
      union REGS r;
      register int i,j;

      for(i=y; *p; i++) {
       goto_xy(x,i);
          r.h.ah=9; /* ������� ������ �������   */
          r.h.bh=0; /* ����� ��������           */
          r.x.cx=1; /* ����� ���������� ������� */
          r.h.al=*p++; /* ������          */
          r.h.bl=attrib; /* �������         */
          int86(0x10,&r,&r);
       }
     }

     /* ���������� ����� ������ */
     void save_video(startx,endx,starty,endy,buf_ptr)
     int   startx,endx,starty,endy;
     unsigned int *buf_ptr;
     {
      union REGS r;
      register int i,j;

      for(i=starty;i<endy;i++)
        for(j=startx;j<endx;j++) {
          goto_xy(j,i);
          r.h.ah=8; /* ������� ������ �������   */
          r.h.bh=0; /* ����� ��������           */
          *buf_ptr++ = int86(0x10,&r,&r);
          putchar(' '); /* ������� ������ */
        }
     }

     /* �������������� ����� ������ */
     void restore_video(startx,endx,starty,endy,buf_ptr)
     int   startx,endx,starty,endy;
     unsigned int *buf_ptr;
     {
      union REGS r;
      register int i,j;

      for(i=starty;i<endy;i++)
        for(j=startx;j<endx;j++) {
          goto_xy(j,i);
          r.h.ah=9; /* ������� ������ �������   */
          r.h.bh=0; /* ����� ��������           */
          r.x.cx=1; /* ����� ���������� ������� */
          r.h.al=*buf_ptr++; /* ������          */
          r.h.bl=*buf_ptr++; /* �������         */
          int86(0x10,&r,&r);
        }
     }

     /* ������� ������ */
     void cls()
     {
      union REGS r;

      r.h.ah=6; /* ��� ��������� ������ */
      r.h.al=0; /* ��� ������� ������ */
      r.h.ch=0; /* ��������� ������ */
      r.h.cl=0; /* ��������� ������� */
      r.h.dh=24; /* �������� ������ */
      r.h.dl=79; /* �������� ������� */
      r.h.bh=7; /* ������� ������ ������ */
      int86(0x10,&r,&r);
     }