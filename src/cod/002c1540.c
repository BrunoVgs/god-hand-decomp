typedef struct {
    char pad[0x50];
    unsigned int flags;
} SceUnit;

extern SceUnit *cSceAtManager_getUnitList(void *mgr);
extern SceUnit *cSceAtManager_getNextUnit(void *mgr, SceUnit *u);

__attribute__((section(".text.func_002C1540")))
void func_002C1540(void *mgr)
{
    SceUnit *u = cSceAtManager_getUnitList(mgr);

    while ((u = cSceAtManager_getNextUnit(mgr, u)) != 0) {
        u->flags &= ~0x40000000;
        if (u->flags & 0x80000000) {
            u->flags |= 0x40000000;
        }
        u->flags &= ~0x80000000;
        u->flags &= ~0x08000000;
        u->flags &= ~0x04000000;
        u->flags &= ~0x02000000;
    }
}
