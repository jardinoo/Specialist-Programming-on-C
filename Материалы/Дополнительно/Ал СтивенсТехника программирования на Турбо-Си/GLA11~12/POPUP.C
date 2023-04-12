#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <dir.h>

static union REGS rg;

unsigned sizeprogram = 48000/16;
unsigned scancode = 52;
unsigned keymask = 8;
char *signature = "POPUP";

char notefile[64];

/*--------------------------------*/
int  resident(char *,void interrupt(*)());
void resinit(void);
void terminate(void);
void restart(void);
void wait(void);
void resident_psp(void);
void interrupted_psp(void);
void exec(void);
void cursor(int,int);
void curr_cursor(int *,int *);

main(argc,argv)
char *argv[];
{
  void interrupt ifunc();
  int ivec;

  if((ivec = resident(signature, ifunc)) != 0) {
    if(argc > 1) {
       rg.x.ax = 0;
       if(strcmp(argv[1],"quit") == 0)
          rg.x.ax = 1;
       else if(strcmp(argv[1],"restart") == 0)
          rg.x.ax = 2;
       else if(strcmp(argv[1],"wait") == 0)
          rg.x.ax = 3;
       if(rg.x.ax)  {
          int86(ivec, &rg, &rg);
          return;
      }
   }
   printf("\n Popup is already resident");
 }
 else   {

   /*load_help("tcprogs.hlp");
   getcwd(notefile, 64);
   if(*(notefile+strlen(notefile)-1) != '\\')
     strcat(notefile,"\\");
   strcat(notefile,"note.pad"); */

   printf("\nResident popup is loaded");
   resinit();
 }
}

/*--------------------------------*/
void interrupt ifunc(bp,di,si,ds,es,dx,cx,bx,ax)
{
   if(ax == 1)       /* quit */
     terminate();
   else if(ax == 2)  /* restart */
     restart();
   else if(ax == 3)  /* wait */
     wait();
}

/*--------------------------------*/
/*void closefiles()
{
 extern FILE *helpfp;

  resident_psp();
  if(helpfp)
    fclose(helpfp);
  interrupted_psp();
} */

/*--------------------------------*/
void popup()
{
  int x,y;

  curr_cursor(&x, &y);
  exec();
  cursor(x,y);
}

/*--------------------------------*/
void cursor(int x, int y)
{
  rg.x.ax=0x0200;
  rg.x.bx=0;
  rg.x.dx=((y<<8) &0xff00) + x;
  int86(16,&rg,&rg);
}
/*--------------------------------*/
void curr_cursor(int *x, int *y)
{
  rg.x.ax=0x0300;
  rg.x.bx=0;
  int86(16,&rg,&rg);
  *x=rg.h.dl;
  *y=rg.h.dh;
}
