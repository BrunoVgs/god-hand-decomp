#include "godhand/cScenario.h"

extern void cTaskWork_exit(struct cTaskWork *w);

__attribute__((section(".text.cScenario_upCutTask")))
void cScenario_upCutTask(void)
{
    int cam = 0;
    int mess;
    int type;

    if (D_003C2F84->upCutCam != 0) {
        cam = 1;
        cScenario_startCamMotion(D_003C2F84, D_003C2F84->upCutCam);
    }
    mess = 0;
    if (D_003C2F84->upCutNo != 0xFFFF) {
        mess = 1;
        cScenario_setMess(D_003C2F84, D_003C2F84->upCutNo);
    }
    type = 1;
    if (cam == 0 && mess == 1)
        type = 2;
    else if (cam == 1 && mess == 0)
        type = 3;
    cScenario_startSoftEvent(D_003C2F84, type);
    if (mess == 1) {
        if ((D_003C2F84->upCutArg ^ 1) & 1)
            cScenario_waitMess(D_003C2F84);
    } else if (cam != 0) {
        if ((D_003C2F84->upCutArg ^ 1) & 1)
            cScenario_waitCam(D_003C2F84);
    }
    cScenario__endSoftEvent(D_003C2F84);
    if (D_003C2F84->upCutAsTask == 1)
        cTaskWork_exit(D_003C2F84->task.cur);
}
