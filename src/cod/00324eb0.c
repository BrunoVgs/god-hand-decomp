/* cygnus-2.96: Sofdec/ADX helper threads (0x324EB0..). */

#include "godhand/adxmThread.h"

extern int adxm_ResumeThread(int tid);
extern int WakeupThread(int tid);

__attribute__((section(".text.func_00324EB0")))
void func_00324EB0(void)
{
    while (D_003C8158 == 0) {
        Obj0000_Increment_D_003C8100_324E98();
    }
    D_003C8160 = 1;
    ExitDeleteThread();
}

__attribute__((section(".text.func_00324F08")))
void func_00324F08(void)
{
    while (D_003C8178 == 0) {
        D_003C8110++;
        func_00325360(D_003C814C);
        if (D_003C81C8 == 0) {
            func_00325FD8();
        }
        D_003C81C8 = 0;
        if (GetD003C80A8_325610() == 1) {
            func_00325360(D_003C8150);
        }
        func_00325E78();
        D_003C80E8 = 1;
        Forward33BC48_33BD48();
        D_003C80E8 = 0;
        SleepThread_3252E0();
    }
    D_003C8180 = 1;
    ExitDeleteThread();
}

__attribute__((section(".text.func_00325010")))
void func_00325010(void)
{
    while (D_003C8188 == 0) {
        D_003C8118++;
        D_003C80F0 = 1;
        if (D_003C81C4 != 0) {
            GS_BGCOLOR = D_003C81C4;
        }
        Forward33BC48_33BD78();
        if (D_003C81C4 != 0) {
            GS_BGCOLOR = 0;
        }
        D_003C80F0 = 0;
        if (D_003C8188 != 0) {
            break;
        }
        SleepThread_3252E0();
    }
    D_003C8190 = 1;
    ExitDeleteThread();
}

__attribute__((section(".text.func_00325100")))
void func_00325100(void)
{
    int busy;

    while (D_003C8198 == 0) {
        D_003C8120++;
        D_003C80F4 = 1;
        busy = Forward33BC48_33BDA8();
        D_003C80F4 = 0;
        if (D_003C80E4 == 1) {
            D_003C80E4 = 0;
            SleepThread_3252E0();
        }
        if (busy == 0) {
            if (GetD003C80A8_325610() == 1) {
                if (adxm_ResumeThread(D_003C8150) == D_003C8150) {
                    func_00325290(D_003C8150);
                }
            }
            if (D_003C80E4 != 1) {
                func_00325FD8();
                D_003C81C8 = 1;
            }
            SleepThread_3252E0();
        }
    }
    D_003C81A0 = 1;
    ExitDeleteThread();
}

__attribute__((section(".text.func_00325DF0")))
void func_00325DF0(void)
{
    if (adxm_ResumeThread(D_003C814C) == D_003C814C) {
        func_00325290(D_003C814C);
    }
    if (GetD003C80A8_325610() == 1) {
        if (adxm_ResumeThread(D_003C8150) == D_003C8150) {
            func_00325290(D_003C8150);
        }
    }
}

__attribute__((section(".text.func_00325E78")))
void func_00325E78(void)
{
    struct ThreadParam info;

    if (D_003C80FC == 1) {
        ReferThreadStatus(D_003C8148, &info);
        if (info.status == 4 || info.status == 0xC) {
            if (WakeupThread(D_003C8148) == D_003C8148) {
                D_003C80FC = 0;
            }
        }
    }
}
