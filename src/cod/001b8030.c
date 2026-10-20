/* sn-2.95.3-136 matched (permuter zero). */
extern void func_001F88A8(void *o, float *s, unsigned char t, float x, float y, float z);
extern int cCamManager_isCk_CamClass(void *mgr, int cls);
extern char D_00463050[];
extern int func_0030F348(void);
__attribute__((section(".text.func_001B8030")))
int func_001B8030(int a0)
{
  int v1 = *((unsigned short *) (((char *) a0) + 0x2FE));
  unsigned long new_var;
  a0 = 0;
  if (v1 < 0x3C0)
  {
    goto done;
  }
  new_var = v1 < 0x400;
  a0 = new_var;
  asm volatile("" : "+r"(a0));
  done:
  return a0;

}
