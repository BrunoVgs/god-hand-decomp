typedef struct { char pad[0x4A]; unsigned char active; char pad2[0x60 - 0x4B]; } DmgCollSlot;
typedef struct { char pad[0x4A]; unsigned char active; char pad2[0x70 - 0x4B]; } FlashSlot;
typedef struct {
    DmgCollSlot dmg[160];
    FlashSlot fl[256];
    char pad[0xACD0 - 0x3C00 - 256 * 0x70];
    int wait;
} DmgFlashMgr;

extern void Trail_snapToSources(void *a0);
extern void FlashDriver_resetFlash(void *a0);
extern void func_001FCF20(void *a0);
extern void cDamageUnit_UpdateDamageCollFlash(void *a0);
extern void NoOp_1FD528(void *a0);

__attribute__((section(".text.func_001FDFD8")))
void func_001FDFD8(DmgFlashMgr *m)
{
    DmgCollSlot *d;
    FlashSlot *f;
    unsigned int i;

    if (m->wait != 0) {
        m->wait--;
        return;
    }
    d = m->dmg;
    do {
        if (d->active) Trail_snapToSources(d);
        d++;
    } while (d < m->dmg + 160);
    i = 0;
    f = m->fl;
    do {
        if (f->active) FlashDriver_resetFlash(f);
        i++;
        f++;
    } while (i < 256);
    d = m->dmg;
    do {
        if (d->active) {
            func_001FCF20(d);
            cDamageUnit_UpdateDamageCollFlash(d);
        }
        d++;
    } while (d < m->dmg + 160);
    f = m->fl;
    i = 0;
    do {
        if (f->active) {
            NoOp_1FD528(f);
            cDamageUnit_UpdateDamageCollFlash(f);
        }
        i++;
        f++;
    } while (i < 256);
}
