/* sn-2.95.3-136 matched 88-byte Phase A functions. */

#include "godhand/vu0.h"

extern void cModel_calcParts(void *);
extern void IK_InverseKinematics(void *, void *);
extern void cModel_calcWorldParts(void *);
extern void *D_00747A4C;
extern char D_00450ED8[];
extern void *SearchData(void *, void *, void *);

__attribute__((section(".text.func_00318468")))
void func_00318468(char *self)
{
    if ((*(int *)(self + 0x250) & 2) != 0)
        return;
    cModel_calcParts(self);
    if (*(int *)(self + 0x258) < 0)
        return;
    IK_InverseKinematics(self + 0x448, self);
    cModel_calcWorldParts(self);
}

__attribute__((section(".text.SearchCameraData")))
void *SearchCameraData(void *key)
{
    void *found = SearchData(D_00747A4C, D_00450ED8, 0);
    if (found == 0)
        return 0;
    return SearchData(found, key, 0);
}
