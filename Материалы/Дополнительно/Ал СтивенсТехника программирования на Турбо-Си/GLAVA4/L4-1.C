                 ���⨭� 4.1: ibmpc.c

/* ibmpc.c */
/*  �㭪樨  ������� �஢��,   �����騥�� �  BIOS �  �������
�।�⢠�  ��  */

#pragma  inline #include <dos.h> static union REGS rg;

/* ������ ����� */

void cursor(int x,int y) {
   rg.x.ax = 0x0200;
   rg.x.bx = 0;
   rg.x.dx = ((y << 8) & 0xff00) + x;
   int86( 16, &rg, &rg);
}

/* �������� ������ ����� */

void curr_cursor( int *x, int *y )
{
   rg.x.ax = 0x0300;
   rg.x.bx = 0;
   int86( 16, &rg, &rg );
   *x = rg.h.dl;
   *y = rg.h.dh;
}

/* ��⠭����� ⨯ ����� */

void set_cursor_type( int t )
{
   rg.x.ax = 0x0100;
   rg.x.bx = 0;
   rg.x.cx = t;
   int86( 16, &rg, &rg );
}
char attrib = 7;

/* ������ ��࠭ */

void clear_screen()
{
   cursor(0, 0);
   rg.h.al = ' ';
   rg.h.ah = 9;
   rg.x.bx = attrib;
   rg.x.cx = 2000;
   int86( 16, &rg, &rg );
}

/* �������� ०�� ࠡ��� ���������஫���*/

int vmode()
{
   rg.h.ah = 15;
   int86( 16, &rg, &rg);
   return rg.h.al;
}

/* �஢���� ������� Scroll Lock */

int scroll_lock()
{
   rg.x.ax = 0x0200;
   int86( 0x16, &rg, &rg);
   return rg.h.al & 0x10;
}
void (* helpfunc)();
int helpkey = 0;
int helping = 0;

/* �ਭ��� ᨬ��� �� ���������� */

int get_char()
{
   int c;
   while (1)   {
       rg.h.ah = 1;
       int86(0x16, &rg, &rg);
       if (rg.x.flags & 0x40)  {
   int86(0x28, &rg, &rg);
   continue;
       }
       rg.h.ah = 0;
       int86(0x16, &rg, &rg);
       if (rg.h.al == 0)
   c = rg.h.ah | 128;
       else
   c = rg.h.al;
       if (c == helpkey && helpfunc)   {
   if (!helping)   {
       helping = 1;
       (*helpfunc)();
       helping = 0;
       continue;
   }
       }
       break;
   }
    return c;
}

/* ������ ��� ᨬ���� � ��� ��ਡ��� � ����������� */

void vroke(unsigned vseg, unsigned adr, unsigned chr)
{
    if (vseg == 45056)     /* �����஬�� ०�� */
poke(vseg, adr, chr);
    else    {
_DI = adr; /* ᬥ饭�� �� ���� ᨬ���� � ���������� */
_ES = vseg; /* ���� ᥣ���� ���������� */
asm cld;
_BX = chr; /* ��ਡ��� � ��� ᨬ���� */
_DX = 986; /* ���ﭨ� ��������� */

/* ����� ��砫� ���⭮�� 室� ���*/

do
    asm in al,dx;
while (_AL & 1);

/* ����� �����襭�� ���⭮�� 室� ��� */

do
    asm in al,dx;
while (!(_AL & 1));
_AL = _BL;
asm stosb;    /* ��������� ᨬ��� */

/* ����� ��砫� ���⭮�� 室� ��� */

do
    asm in al,dx;
while (_AL & 1);

/* ����� �����襭�� ���⭮�� 室� ��� */

do
    asm in al,dx;
while (!(_AL & 1));
_AL = _BL;
asm stosb;     /* ��������� ��ਡ��� */
     }
}

/* ����� ��� ᨬ���� � ��� ��ਡ��� �� ���������� */

int vpeek(unsigned vseg, unsigned adr)
{
    int ch, at;
    if (vseg == 45056)   /* �����஬�� ०�� */
return peek(vseg, adr);
    asm push ds;
    _DX = 986;    /* ���ﭨ� ��������� */
    _DS = vseg;   /* ���� ᥣ���� ���������� */
    _SI = adr;/* ᬥ饭�� �� ���� ᨬ���� � ���������� */
    asm cld;

    /* ����� ��砫� ���⭮�� 室� ��� */

    do
asm in al,dx;
    while (_AL & 1);

    /* ����� �����襭�� ���⭮�� 室� ��� */

    do
       asm in al,dx;
    while (!(_AL & 1));
    asm lodsb;     /* ����� ᨬ��� */
    _BL = _AL;

    /* ����� ��砫� ���⭮�� 室� ��� */

    do
asm in al,dx;
    while (_AL & 1);

    /* ����� �����襭�� ���⭮�� 室� ��� */

    do
asm in al,dx;
    while (!(_AL & 1));
    asm lodsb;     /* ����� ��ਡ�� */
    _BH = _AL;
    _AX = _BX;
    asm pop ds;
    return _AX;
}

/* keys.h */

#define HT          9
#define RUBOUT      8
#define BELL        7
#define ESC        27
#define SHIFT_HT  143
#define CTRL_T     20
#define CTRL_B      2
#define CTRL_D      4
#define ALT_D     160

#define F1   187
#define F2   188
#define F3   189
#define F4   190
#define F5   191
#define F6   192
#define F7   193
#define F8   194
#define F9   195
#define F10  196

#define HOME   199
#define UP     200
#define PGUP   201
#define BS     203
#define FWD    205
#define END    207
#define DN     208
#define PGDN   209
#define INS    210
#define DEL    211

#define CTRL_HOME   247
#define CTRL_BS     243
#define CTRL_FWD    244
#define CTRL_END    245
