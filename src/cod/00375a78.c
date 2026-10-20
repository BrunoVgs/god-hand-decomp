#include "godhand/sndBank.h"
extern void *func_003A52F0(void *, int, int);

__attribute__((section(".text.func_00375A78")))
void func_00375A78(short index)
{
    func_003A52F0(&D_0076EA50[index], 0, sizeof(SndBank));
}
