/* cygnus-2.96: NM closer handoff. */
/* cygnus-2.96: func_003526D0, split from src/cod/sa_nm_003525f0.c by the NM closer. */
#include "godhand/sftim.h"

int func_003526D0(SftimHn *hn, SftimInfo *info);
void func_00352790(SftimHn *hn, SftimInfo *info, int time, int update);

/* Register allocation: retail builds the result in v0 directly; ours uses a3 plus a move. */
__attribute__((section(".text.func_003526D0")))
int func_003526D0(SftimHn *hn, SftimInfo *info)
{
    SftimTc tc;
    int now;
    int unit;
    int start;
    int len;

    if (hn->tim.rec[1].valid == 0) {
        return 0;
    }
    tc = hn->tim.tc;
    SFTIM_Tc2Time(&tc, &now, &unit);
    SFTIM_Tc2Time(&hn->tim.rec[1].tc, &start, &unit);
    len = GetArrayElemA0C_35A1C8(hn, 0x35) * unit;
    if (now > start) {
        if (now < start + len) return 0;
        return 1;
    }
    return 1;
}

/* Register allocation: retail loads rate straight into a1; ours goes through v1 (8 insns). */

/* Retail computes the field parity before the shift, and allocates the non-drop h/m/s chain differently (12 insns). */

/* Scheduling and register allocation of the div/mod chain differ (39 insns). */

/* Retail keeps &rec[0] in a register and does not write the difference back to the stack. */
