/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"

extern int irand(void);

/* The settings record the node reads: the bytes from 0x18C and a vector at 0x13C. */
typedef struct ShakeCfg {
    char unk000[0xBE];
    signed char link;           /* 0xBE */
    char unkBF[0x7D];
    float vx, vy, vz;           /* 0x13C */
    char unk148[0x44];
    unsigned char hpBase;       /* 0x18C */
    signed char hpRand;         /* 0x18D */
    unsigned char kind;         /* 0x18E */
    signed char rateA;          /* 0x18F */
    signed char rateB;          /* 0x190 */
    char unk191[6];
    unsigned char flag;         /* 0x197 */
} ShakeCfg;

typedef struct ShakeSrc {
    char unk00[0x4E];
    unsigned char link;         /* 0x4E */
    char unk4F;
    int target;                 /* 0x50 */
    char unk54[0xC];
    cVec pos;                   /* 0x60 */
} ShakeSrc;

typedef struct ShakeInit {
    char unk000[0x110];
    ShakeCfg *cfg;              /* 0x110 */
    int owner;                  /* 0x114 */
    char unk118[0x19C];
    float rateA;                /* 0x2B4 */
    float rateB;                /* 0x2B8 */
    unsigned short hp;          /* 0x2BC */
    unsigned char kind;         /* 0x2BE */
    unsigned char link;         /* 0x2BF */
    int target;                 /* 0x2C0 */
    char unk2C4[0xC];
    cVec pos;                   /* 0x2D0 */
    char unk2E0[1];
} ShakeInit;

#define SHAKE_RATE_A_SCALE  0.025f
#define SHAKE_RATE_B_SCALE  0.5f

/* Set the node up from its settings and the source record: starting hit points (minus a random part), kind and rates,
 * then its target and start position: the source's when it has a target, else the settings' own. Returns 1. */
__attribute__((section(".text.func_002F4EB8")))
int func_002F4EB8(ShakeInit *self, ShakeSrc *src)
{
    int rnd;
    int range;
    unsigned int div;
    ShakeCfg *cfg = self->cfg;
    ShakeCfg *cfg2;
    ShakeCfg *cfg3;

    self->hp = (signed char)cfg->hpBase;
    range = cfg->hpRand;
    div = range;
    if (range != 0) {
        self->hp = self->hp - irand() % div;
        if ((short)self->hp <= 0)
            self->hp = 0;
    }
    cfg2 = self->cfg;
    self->kind = cfg2->kind;
    self->rateA = cfg2->rateA * SHAKE_RATE_A_SCALE;
    self->rateB = cfg2->rateB * SHAKE_RATE_B_SCALE;
    self->unk2E0[0] = cfg2->flag;
    if (src->target != 0) {
        self->target = src->target;
        self->link = src->link;
        cVec_copy3(&self->pos, &src->pos);
    } else {
        if (self->owner != 0 && cfg2->link >= 0) {
            self->target = self->owner;
            self->link = cfg2->link;
        }
        cfg3 = self->cfg;
        self->pos.x = cfg3->vx;
        self->pos.y = cfg3->vy;
        self->pos.z = cfg3->vz;
    }
    return 1;
}
