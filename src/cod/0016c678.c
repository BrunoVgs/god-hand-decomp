/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"

extern void Obj0000_Set_D_007474A0_Fields_5D8_5E0(void *self);
extern void AddToActiveList_138F40(void *list, int arg);
extern void pl00_SubscreenMode(void *player, int mode);
extern int cIDBase_release(void *idBase);
extern void func_00161590(void *self);
extern void Forward2D9458_2D98A0(void *p);
extern char D_00463050[];
extern char D_00604700[];
extern char **D_003C2384;

#define PLAYER_STATE_FREE  10           /* player state set while the screen closes */

typedef struct PlayerRef {
    char unk000[0x100];
    cVec turnTo;                        /* 0x100 */
    char unk110[0x2C0 - 0x110];
    int state;                          /* 0x2C0 */
} PlayerRef;

/* The screen is itself a cIDBase and owns two more. */
typedef struct Screen16C678 {
    char idBase[0x170];                 /* 0x000 */
    char idBaseB[0x264 - 0x170];        /* 0x170 */
    PlayerRef *player;                  /* 0x264 */
    char unk268[8];
    cVec target;                        /* 0x270 where the player is turned to */
    char unk280[0x10];
    char idBaseC[0x10];                 /* 0x290 */
} Screen16C678;

/* Closes the screen: hands the player back, releases the three id bases,
 * clears the host's two words and tells the list to move on. */
__attribute__((section(".text.func_0016C678")))
void func_0016C678(Screen16C678 *self)
{
    char *host;
    Obj0000_Set_D_007474A0_Fields_5D8_5E0(self);
    AddToActiveList_138F40(D_00463050, 0);
    cVec_copy3(&self->player->turnTo, &self->target);
    self->player->state = PLAYER_STATE_FREE;
    pl00_SubscreenMode(self->player, 0);
    cIDBase_release(self->idBaseC);
    cIDBase_release(self->idBaseB);
    cIDBase_release(self);
    host = *D_003C2384;
    *(int *)(host + 0x2C) = 0;
    *(int *)(host + 0x28) = 0;
    func_00161590(self);
    Forward2D9458_2D98A0(D_00604700);
}
