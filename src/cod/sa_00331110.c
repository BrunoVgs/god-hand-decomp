/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
/* cygnus-2.96 (drop-reorder): func_00331110, split from src/cod/sa_nm_00331070.c by the NM closer. */

typedef signed char Sint8;
typedef char Char8;
typedef int Sint32;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;
typedef Sint32 Bool;
typedef unsigned char u_char;

typedef struct {
    u_char trycount;
    u_char spindlctrl;
    u_char datapattern;
    u_char pad;
} sceCdRMode;

typedef struct srd_obj {
    Sint8 used;
    Sint8 devtype;
    Sint8 stat;
    Char8 rsv;
    Sint32 break_flg;
    Uint32 d_lsn;
    Uint32 d_sct;
    void *d_buf;
    sceCdRMode d_mode;
    void *h_buf;
    Uint64 h_byte;
    Uint64 h_skpos;
    int h_fd;
    int err_code;
} SRD_OBJ, *SRD;

extern void *memcpy(void *dst, const void *src, unsigned int n);
extern int Forward33B568_33B688(void);
extern int Forward33B5C8_33B6B8(void);
extern int func_003B1F28(const char *fmt, ...);
extern void func_00330FB8(void);
extern void PushGlobalD8478History_331C78(int code);
extern int func_00398DA0(int mode);

extern SRD_OBJ D_003D8410;              /* srd_obj */
extern volatile Sint32 D_003D8474;      /* destroy count */
extern char D_00453E30[];               /* "SRD: SRD_Destroy, invalidate srd handle..." */
extern char D_00453E70[];

__attribute__((section(".text.func_00331110")))
Bool func_00331110(SRD srd, Uint32 lsn, Uint32 nsct, void *buf, sceCdRMode *mode)
{
    Bool ret;
    int busy;

    ret = 0;
    PushGlobalD8478History_331C78(0x1200);
    busy = func_00398DA0(1);
    PushGlobalD8478History_331C78(0x1201);
    if (busy == 1) {
        return 0;
    }
    Forward33B568_33B688();
    if (srd->stat == 0 || srd->stat == 3 || srd->stat == 9) {
        srd->devtype = 1;
        srd->stat = 1;
        srd->d_lsn = lsn;
        srd->d_mode = *mode;
        srd->d_sct = nsct;
        srd->d_buf = buf;
        srd->break_flg = 0;
        ret = 1;
    }
    Forward33B5C8_33B6B8();
    return ret;
}

