/* cygnus-2.96 (drop-reorder): SFX stream decoder callback setup (0x35F698). */

#include "godhand/sfxlib.h"

extern void Obj35E8_SetField_68(SfxStm *stm, void *fn);
extern void Obj35E8_SetField_6C(SfxStm *stm, void *fn);
extern void Obj35E8_SetField_70(SfxStm *stm, void *fn);
extern void Obj35E8_SetIndirect_30_18(SfxStm *stm, void *fn);
extern void Obj35E8_SetIndirect_30_1C(SfxStm *stm, void *fn);
extern void Obj35E8_SetIndirect_30_20(SfxStm *stm, void *fn);
extern void func_0035EF78(SfxStm *stm, SfxInf *inf, int c);

extern void func_003634E0(void);
extern void func_00366840(void);
extern void func_00366678(void);
extern void func_00365EC0(void);
extern void func_00366368(void);
extern void func_00366110(void);
extern void func_003665C0(void);

__attribute__((section(".text.func_0035F698")))
void func_0035F698(SfxStm *stm, SfxInf *inf, int c)
{
    void *fn = 0;
    void *dec;

    stm->f50 = 0;
    dec = 0;
    if (inf->kind == 1) {
        dec = (void *)func_003634E0;
    }
    Obj35E8_SetField_68(stm, dec);
    if (inf->kind == 1) {
        fn = (void *)func_00366840;
    } else if (inf->kind == 2) {
        fn = (void *)func_00366678;
    }
    Obj35E8_SetField_6C(stm, fn);
    Obj35E8_SetIndirect_30_18(stm, (void *)func_00365EC0);
    Obj35E8_SetIndirect_30_20(stm, (void *)func_00366368);
    Obj35E8_SetIndirect_30_1C(stm, (void *)func_00366110);
    Obj35E8_SetField_70(stm, (void *)func_003665C0);
    func_0035EF78(stm, inf, c);
}
