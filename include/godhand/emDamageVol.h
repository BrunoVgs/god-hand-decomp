#ifndef GODHAND_EMDAMAGEVOL_H
#define GODHAND_EMDAMAGEVOL_H

/* Enemy work offsets used by the damage-volume setup family (sa_001932d8.c and its clones). */
#define EM_COL_A        0x548   /* short */
#define EM_COL_B        0x54A   /* short */
#define EM_WORK_5E4     0x5E4
#define EM_WORK_5E8     0x5E8
#define EM_WORK_5EC     0x5EC
#define EM_WORK_5F0     0x5F0
#define EM_TARGET       0x5F4   /* short, -1 = none */
#define EM_WORK_5F6     0x5F6   /* short */
#define EM_DMG_TAKE     0x600
#define EM_DMG_GIVE     0x604
#define EM_SUB_PTR      0x608
#define EM_SUB_KIND     0x60C   /* unsigned char */
#define EM_SUB_BUF      0x620

/* Takes only the enemy work: it clobbers a1/a2 at entry. phase_a_sn_288.c and phase_a_sn_300.c
 * still declare a 4-argument form, so this stays out of the shared enemy headers. */
extern int func_001C28A0(char *p);

#endif /* GODHAND_EMDAMAGEVOL_H */
