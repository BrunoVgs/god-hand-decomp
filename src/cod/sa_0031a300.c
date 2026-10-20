/* sn-2.95.3-136: double-buffered DMA packet chain setup and the VIF1 kick (0x31A300..). */

#include "godhand/gameWork.h"

typedef unsigned int u_int;

typedef struct {
    int lo;
    int hi;
} Range31A3;

typedef struct {
    char pad[0xB00];
    Range31A3 slot[1];
} Obj31A3;

__attribute__((section(".text.func_0031A300")))
void func_0031A300(Obj31A3 *self, int i, int base)
{
    self->slot[i].lo = base;
    self->slot[i].hi = base + 0x80;
}

__attribute__((section(".text.func_0031A320")))
void func_0031A320(Obj31A3 *self, int i)
{
    self->slot[i].lo = 0;
    self->slot[i].hi = 0;
}

static inline int pktIsMode1(void)
{
    return D_007474A0.mode == 1;
}

#define PKT(n) set->pkt[n][odd].data
#define LINK(a, b) SetPackedFields10And18_14FF60((int)(a), (int *)(b))

__attribute__((section(".text.func_0031A338")))
void func_0031A338(PktSet31A3 *set)
{
    int odd = D_007474A0.frame & 1;
    char *p0, *p1, *p2, *p3, *p5, *p6, *p7, *p8, *p9;

    func_0014FE78(p0 = PKT(0));
    func_0014FE78(p1 = PKT(1));
    func_0014FE78(p2 = PKT(2));
    func_0014FE78(p3 = PKT(3));
    func_0014FE78(p5 = PKT(5));
    func_0014FE78(p6 = PKT(6));
    func_0014FE78(p7 = PKT(7));
    func_0014FE78(p8 = PKT(8));
    func_0014FE78(p9 = PKT(9));
    if (!(D_007474A0.flags & GAMEWORK_SKIP_PKT_1_3)) {
        LINK(p0, p1);
        LINK(p1, p3);
        LINK(p3, p2);
        LINK(p2, p5);
        LINK(p5, p6);
        LINK(p6, p7);
        LINK(p7, p8);
        LINK(p8, p9);
    } else {
        LINK(p0, p5);
        LINK(p5, p6);
        LINK(p6, p7);
        LINK(p7, p8);
        LINK(p8, p9);
    }
    if (pktIsMode1()) {
        func_0014FE78(PKT(10));
        LINK(PKT(9), PKT(10));
    }
}

__attribute__((section(".text.func_0031A538")))
void func_0031A538(int *tbl)
{
    int odd = D_007474A0.frame & 1;

    if (D_007474A0.flags & GAMEWORK_IN_INTERRUPT) {
        iFlushCache(0);
    } else {
        FlushCache(0);
    }
    func_003950F8(0, 0);
    *(volatile u_int *)0x1000E010 = 2;
    *(volatile u_int *)0x1000E020 = 2;
    *(volatile u_int *)0x10009020 = 0;
    *(volatile u_int *)0x10009030 = tbl[odd * 32];
    *(volatile u_int *)0x10009000 = 0x45;
    *(volatile u_int *)0x10009000 = 0x145;
}
