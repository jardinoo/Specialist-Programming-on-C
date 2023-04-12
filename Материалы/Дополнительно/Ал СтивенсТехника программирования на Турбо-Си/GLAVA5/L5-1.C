
        Листинг 5.1: vidpoke.c

/* vidpoke.c */

#define VSEG 0x6800
char vdata [] =  "Что сделал Кан?";
main()
{
char *vp;
int v;
for (v=0, vp = vdata; *vp; v +=2, vp++)
     poke ( VSEG, v, 0x700| *vp);
}
