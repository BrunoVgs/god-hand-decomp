#include "godhand/cScenario.h"
#include "godhand/gameWork.h"
extern void func_0031A0E8(void *p);
extern void InitSubBufferPool_2C3280(cScenario *sc);
extern void EntTable_init(void *p, int a1, int a2, int a3);
extern void func_002D51C0(void *p, int a1, int a2);
extern void TaskPool_runAll(void *p);
extern void FileBuf_init(void);
extern char D_00754C80[];

__attribute__((section(".text.func_0030B698")))
void func_0030B698(void)
{
    D_00747A24 |= 0x4000;
    func_0031A0E8(D_00754C80);
    InitSubBufferPool_2C3280(D_003C2F84);
    EntTable_init(&D_00752C00, 4, 0x3000, 0x20);
    func_002D51C0(&D_00752C00, 0, 0x8000);
    func_002D51C0(&D_00752C00, 1, 0x8000);
    TaskPool_runAll(&D_00752C00);
    FileBuf_init();
}
