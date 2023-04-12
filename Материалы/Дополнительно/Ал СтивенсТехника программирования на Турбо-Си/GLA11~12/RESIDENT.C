#include <dos.h>
#include <stdio.h>

static union REGS rg;
static struct SREGS seg;
static unsigned mcbseg;
static unsigned dosseg;
static unsigned dosbusy;
static unsigned enddos;
char far *intdta; 
static unsigned intsp;
static unsigned intss;
static char far *mydta;
static unsigned myss;
static unsigned stack;
static unsigned ctrl_break;
static unsigned mypsp;
static unsigned intpsp;
static unsigned pids[2];
static int pidctr = 0;
static int pp;
static void interrupt (*oldtimer)();
static void interrupt (*old28)();
static void interrupt (*oldkb)();
static void interrupt (*olddisk)();
static void interrupt (*oldcrit)();
static void interrupt (*ZeroDivVector)();
void interrupt newtimer();
void interrupt new28();
void interrupt newkb();
void interrupt newdisk();
void interrupt newcrit();
extern unsigned sizeprogram;
extern unsigned scancode;
extern unsigned keymask;
static int resoff = 0;
static int running = 0;
static int popflg = 0;
static int diskflag = 0;
static int kbval;
static int cflag;

void dores(),pidaddr();
/*------------------------------------------------*/
void resinit()
{
  segread(&seg);
  myss=seg.ss;
  
  rg.h.ah=0x34;
  intdos(&rg, &rg);
  dosseg = _ES;
  dosbusy=rg.x.bx;
  
  mydta=getdta();

  pidaddr();
  
  oldtimer=getvect(0x1c);
  old28=getvect(0x28);
  oldkb=getvect(9);
  olddisk=getvect(0x13);
  
  setvect(0x1c,newtimer);
  setvect(0x9,newkb);
  setvect(0x28,new28);
  setvect(0x13,newdisk);
  
  stack=(sizeprogram - (seg.ds - seg.cs)) * 16 - 300;
  
  setvect(0,ZeroDivVector);
  
  rg.x.ax=0x3100;
  rg.x.dx=sizeprogram;
  intdos(&rg, &rg);
}

/*------------------------------------------------*/
void interrupt newdisk(bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flgs)
{ 
  diskflag++;
  (*olddisk)();
  ax=_AX;
  cx=_CX;
  dx=_DX;
  newcrit();
  flgs=cflag;
  --diskflag;
}

/*------------------------------------------------*/
void interrupt newcrit(bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flgs)
{
  ax=0;
  cflag=flgs;
}

/*------------------------------------------------*/
void interrupt newkb()
{
  if(inportb(0x60) == scancode) {
    kbval=peekb(0,0x417);
    if(!resoff && ((kbval & keymask) & keymask) == 0) { /* !!!!!!! & */
      kbval=inportb(0x61);
      outportb(0x61,kbval|0x80);
      outportb(0x61,kbval);
      outportb(0x20,0x20);
      if(!running)
        popflg=1;
      return;
   }
 }
 (*oldkb)();
 }

/*------------------------------------------------*/
void interrupt newtimer()
{
  (*oldtimer)();
  if(popflg && peekb(dosseg, dosbusy) == 0)
    if(diskflag == 0) {
      outportb(0x20,0x20);
      popflg=0;
      dores();
    }
}

/*------------------------------------------------*/
void interrupt new28()
{
  (*old28)();
  if(popflg && peekb(dosseg, dosbusy) != 0) {
      popflg=0;
      dores();
    }
}

/*------------------------------------------------*/
resident_psp()
{
  intpsp=peek(dosseg,*pids);
  for(pp=0; pp < pidctr; pp++)
    poke(dosseg,pids[pp],mypsp);
}

/*------------------------------------------------*/
interrupted_psp()
{
  for(pp=0; pp < pidctr; pp++)
    poke(dosseg,pids[pp],intpsp);
}
/*------------------------------------------------*/
void dores()
{
  running=1;
  disable();
  intsp=_SP;
  intss=_SS;
  _SP=stack;
  _SS=myss;
  enable();
  oldcrit = getvect(0x24);
  setvect(0x24,newcrit);
  rg.x.ax=0x3300;
  intdos(&rg, &rg);
  ctrl_break=rg.h.dl;
  rg.x.ax=0x3301;
  rg.h.dl=0;
  intdos(&rg, &rg);
  intdta=getdta();
  setdta(mydta);
  resident_psp();
  popup();
  interrupted_psp();
  setdta(intdta);
  setvect(0x24,oldcrit);
  rg.x.ax=0x3301;
  rg.h.dl=ctrl_break;
  intdos(&rg, &rg);
  disable();
  _SP=intsp;
  _SS=intss;
  enable();
  running=0;
}

/*------------------------------------------------*/
static int avec=0;
unsigned resident(signature, ifunc)
char *signature;
void interrupt (*ifunc)();
{
   char *sg;
   unsigned df;
   int vec;

   segread(&seg);
   df=seg.ds - seg.cs;
   for(vec=0x60; vec < 0x68; vec++) {
      if(getvect(vec) == NULL)  {
        if(!avec)
          avec=vec;
        continue;
      }
      for(sg=signature; *sg; sg++)
        if(*sg!=peekb(peek(0,2+vec*4)+df,(unsigned)sg))
           break;
        if(!*sg)
           return vec;
   }
   if(avec) 
      setvect(avec, ifunc);
   return 0;
}

/*------------------------------------------------*/
static void pidaddr()
{
   unsigned adr=0;
   
   rg.h.ah=0x51;
   intdos(&rg, &rg);
   mypsp=rg.x.bx;
   
   rg.h.ah=0x52;
   intdos(&rg, &rg);
   enddos=_ES;
   enddos = peek(enddos, rg.x.bx-2);
   
   while(pidctr < 2 &&
       (unsigned)((dosseg<<4) + adr) < (enddos<<4)) {
    if(peek(dosseg, adr) == mypsp)  {
       rg.h.ah=0x50;
       rg.x.bx=mypsp+1;
       intdos(&rg, &rg);
       if(peek(dosseg, adr) == mypsp +1)
         pids[pidctr++]=adr;
       rg.h.ah=0x50;
       rg.x.bx=mypsp;
       intdos(&rg, &rg);
    }
    adr++;
  }
}
       
/*------------------------------------------------*/
static resterm()
{
 /* closefiles();*/

  setvect(0x1c,oldtimer);
  setvect(9,oldkb);
  setvect(0x28,old28);
  setvect(0x13,olddisk);
  setvect(avec, (void interrupt (*)()) 0);

  rg.h.ah=0x52;
  intdos(&rg, &rg);
  mcbseg=_ES;
  mcbseg=peek(mcbseg, rg.x.bx-2);
  
  segread(&seg);
  while(peek(mcbseg, 0) == 0x4d)  {
       if(peek(mcbseg, 1) == mypsp) {
         rg.h.ah=0x49;
         seg.es=mcbseg+1;
         intdosx(&rg, &rg, &seg);
       }
       mcbseg+=peek(mcbseg,3)+1;
  }
}

/*------------------------------------------------*/
terminate()
{
  if(getvect(0x13) == (void interrupt (*)()) newdisk)
    if(getvect(9) == newkb)
       if(getvect(0x28) == new28)
          if(getvect(0x1c) == newtimer) {
             resterm();
             return;
          }
  resoff=1;
}

    
/*------------------------------------------------*/
restart()
{
  resoff=0;
}
/*------------------------------------------------*/
wait()
{
  resoff=1;
}

