/* cygnus-2.96 matched TU. */
#include "godhand/mwsfd.h"
extern int Obj34D8_SetGlobalEE0B8_IfField48(SfdHn *sfd);
extern int func_0034DD70(int object, int error);

/* Enable concatenated playback on a valid Sofdec handle. */
__attribute__((section(".text.SFD_SetConcatPlay")))
int SFD_SetConcatPlay(SfdHn *sfd)
{
    if (Obj34D8_SetGlobalEE0B8_IfField48(sfd) != 0) {
        return func_0034DD70(0, 0xFF000161);
    }
    func_0035A000(sfd, 0x31, 1);
    return 0;
}
