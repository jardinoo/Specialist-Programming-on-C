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
      "Яблоко",
      "Апельсин",
      "Груша",
      "Грейпфрут",
      "Малина",
      "Клубника"
     };

     char *color[]={
      "Красный",
      "Желтый",
      "Оранжевый",
      "Зеленый"
     };

     char *apple_type[] = {
      "Красный деликатес",
      "Джонатан",
      "Белый налив",
      "Антоновка"
     };

     main()
     {
      int i;

     cls();
     goto_xy(0,0);
     for(i=0;i<25;i++)
      printf("Это тест исчезающего меню\n");
     popup(fruit,"яагрмк",6,1,3,BORDER);
     popup(color,"кжоз",4,5,10,BORDER);
     popup(apple_type,"кдба",4,10,18,BORDER);
     }

     /* вывести исчезающее меню и вернуть выбор
        возвращает -2, если меню не может быть создано
        возвращает -1, если пользователь нажал клавишу ESC
        в остальных случаях она возвращает номер выбранной
        альтернативы, начиная с 0 */
     int popup(menu,keys,count,x,y,border)
     char *menu[];  /* текст меню */
     char *keys;    /* горячие клавиши */
     int count;     /* число альтернатив */
     int x,y;       /* координаты левого верхнего угла */
     int border;    /* если 0 то без рамки */
     {
      register int i,len;
	  int endx,endy,choice;
      unsigned char *p;

      if((x>24)||(x<0)||(y>79)||(y<0)) {
       printf(" выход за пределы экрана");
       return -2;
      }
     /* вычисление размеров */
     len=0;
     for(i=0;i<count;i++)
      if(strlen(menu[i]) > len) len=strlen(menu[i]);
     endy=len+2+y;
     endx=count+1+x;
     if((endx+1>24) || (endy+1>79)) {
       printf(" выход за пределы экрана");
       return -2;
      }
     /* размещение памяти для видео буфера */
     p=(unsigned int *)malloc((endx-x+1)*(endy-y+1));
      if(!p) exit(1); /* Вы можете здесь сами обработать ошибку */

     /* сохранение части экрана */
	 save_video(x,endx+1,y,endy+1,p);

     if(border) draw_border(x,y,endx,endy);

     /* высвечивание меню на своем месте */
	 display_menu(menu,x,y,count);

     /* ввести выбор пользователя */
	 choice=get_resp(x,y,count,menu,keys);

     /* восстановление части экрана */
	 restore_video(x,endx+1,y,endy+1,p);
     free(p);
     return choice;
     }

     /* высвечивание меню на своем месте */
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

     /* ввести выбор пользователя */
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
     /* осветить первый выбор */
     goto_xy(x,y);
     write_video(x,y,menu[0],REV_VID);

     for(;;) {
      while(!bioskey(1)); /* ждать нажатия */
      c.i=bioskey(0);

     /* вернуть выбор в номальный режим */
     goto_xy(arrow_choice,y);
     write_video(x+arrow_choice,y,
			 menu[arrow_choice],NORM_VID);
     if(c.ch[0]) { /* обычная клавиша */
	  key_choice= is_in(keys,tolower(c.ch[0]));
     if(key_choice) return key_choice-1;
     switch(c.ch[0]) {
       case '\r' : return arrow_choice;
       case ' '  : arrow_choice++;
                   break;
      case ESC   : return -1; /* выйти */
        }
     }
     else { /* специальная клавиша */
      switch(c.ch[1]) {
       case 72 : arrow_choice--; /* стрелка вниз */
                 break;
       case 80 : arrow_choice++; /* стрелка вверх */
                 break;

          }
       }
     if(arrow_choice==count) arrow_choice=0;
     if(arrow_choice<0) arrow_choice=count-1;
         /* подсветить выбранную опцию */
      goto_xy(x+arrow_choice,y);
      write_video(x+arrow_choice,y,menu[arrow_choice],REV_VID);
      }
     }

     /* вывод строки с определенным атрибутом */
     void write_video(x,y,p,attrib)
     int x,y;
     char *p;
     int attrib;
     {
      union REGS r;
      register int i,j;

      for(i=y; *p; i++) {
       goto_xy(x,i);
          r.h.ah=9; /* функция записи символа   */
          r.h.bh=0; /* видео страница           */
          r.x.cx=1; /* число повторений символа */
          r.h.al=*p++; /* символ          */
          r.h.bl=attrib; /* атрибут         */
          int86(0x10,&r,&r);
       }
     }

     /* сохранение части экрана */
     void save_video(startx,endx,starty,endy,buf_ptr)
     int   startx,endx,starty,endy;
     unsigned int *buf_ptr;
     {
      union REGS r;
      register int i,j;

      for(i=starty;i<endy;i++)
        for(j=startx;j<endx;j++) {
          goto_xy(j,i);
          r.h.ah=8; /* функция чтения символа   */
          r.h.bh=0; /* видео страница           */
          *buf_ptr++ = int86(0x10,&r,&r);
          putchar(' '); /* очистка экрана */
        }
     }

     /* восстановление части экрана */
     void restore_video(startx,endx,starty,endy,buf_ptr)
     int   startx,endx,starty,endy;
     unsigned int *buf_ptr;
     {
      union REGS r;
      register int i,j;

      for(i=starty;i<endy;i++)
        for(j=startx;j<endx;j++) {
          goto_xy(j,i);
          r.h.ah=9; /* функция записи символа   */
          r.h.bh=0; /* видео страница           */
          r.x.cx=1; /* число повторений символа */
          r.h.al=*buf_ptr++; /* символ          */
          r.h.bl=*buf_ptr++; /* атрибут         */
          int86(0x10,&r,&r);
        }
     }

     /* очистка экрана */
     void cls()
     {
      union REGS r;

      r.h.ah=6; /* код прокрутки экрана */
      r.h.al=0; /* код очистки экрана */
      r.h.ch=0; /* начальная строка */
      r.h.cl=0; /* начальная колонка */
      r.h.dh=24; /* конечная строка */
      r.h.dl=79; /* конечная колонка */
      r.h.bh=7; /* очистка пустой строки */
      int86(0x10,&r,&r);
     }