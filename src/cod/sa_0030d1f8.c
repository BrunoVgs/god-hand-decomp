/* sn-2.95.3-136, as=sn: NM closer handoff. */
/* sn-2.95.3-136, as=sn: func_0030D1F8, split from src/cod/sa_nm_0030d1f8.c by the NM closer. */
/* NM, not registered. sn-2.95.3-136: EE timer 0 interrupt and the VRAM clear at 0x30D1F8. */

typedef unsigned int u_int;
typedef struct { unsigned char data[0x60]; } sceGsLoadImage;

#define T0_COUNT (*(volatile u_int *)0x10000000)
#define T0_MODE  (*(volatile u_int *)0x10000010)
#define T0_COMP  (*(volatile u_int *)0x10000020)
#define INTC_TIM0 9

extern int func_0030D190(int cause);
extern int AddIntcHandler(int cause, int (*handler)(int), int next);
extern int func_003B0740(int cause);
extern unsigned char D_00753DC0[0x400];
extern int sceGsSetDefLoadImage(sceGsLoadImage *lp, short dbp, short dbw, short dpsm, short x, short y, short w, short h);
extern void FlushCache(int op);
extern int func_00395758(sceGsLoadImage *lp, void *src);
extern int func_003950F8(int mode, int timeout);

__attribute__((section(".text.func_0030D1F8")))
void func_0030D1F8(void)
{
    T0_COUNT = 0;
    T0_COMP = 0x2589;
    T0_MODE |= 0x1C2;
    AddIntcHandler(INTC_TIM0, func_0030D190, 0);
    func_003B0740(INTC_TIM0);
}

/* 16 words short: retail keeps the short-argument shifts and the 0x400000>>8 block count unfolded. */

/* The parts of the game work block at D_007474A0 this function names. */
typedef struct GameWorkBoot {
    char pad000[0x554];
    void *sysData;              /* 0x554 system data file */
    void *langData;             /* 0x558 language data file */
    char pad55C[0x56C - 0x55C];
    unsigned int language;      /* 0x56C */
    char pad570[0x584 - 0x570];
    int flags;                  /* 0x584 */
    char pad588[0x598 - 0x588];
    int flags598;               /* 0x598 */
} GameWorkBoot;

typedef struct cTaskWorkRef {
    int unk0;
    int task;                   /* 0x4 */
} cTaskWorkRef;

extern GameWorkBoot D_007474A0;
extern char *D_003C3BC8[];      /* data file paths */
extern char D_005FEE00[];
extern char D_00583F20[];       /* the DVD reader */
extern char D_00754200[];       /* the load heap */
extern int D_003C2380;
extern void *D_003C23A4;
extern void **D_003C2384;
extern void *D_003C2388;
extern char D_00450540[];
extern cTaskWorkRef D_00752C00;

extern void cSnd_LoadStartupBanks(void *a0);
extern int cDvd_ReadAlloc(void *dvd, char *path, void **out, void *heap, int t0, int t1, int t2, int t3);
extern void cDvd_CheckWaitFrame(void *dvd, int req);
extern void func_002A4970(int font);
extern void cMenu_loadDataTables(void *a0);
extern int SearchData(void *data, void *name, int a2);
extern void cIDManager_systemInit(void *mgr, int id);
extern void cTaskManager_execute(void *mgr, void (*entry)(void), int arg);
extern void cTaskWork_exit(int task);
extern void cMc_taskBody(void);
extern void func_002A5998(void);
extern void func_0030D5C8(void);

/* Also needs compile_units[].extern_jtbl = D_00450550 (the language switch table), which sa_register cannot set.
 * Retail anchors the game-work addresses at D_007474A0+0x584 (flags) and derives the rest from it; ours anchors at the base. */
