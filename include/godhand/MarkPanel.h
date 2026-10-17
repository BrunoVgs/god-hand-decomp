/* MarkPanel: a screen object that owns three scroll-layer marks. Each mark
 * has a scroll layer id and a flag halfword (bit 15 = start lit, bit 14 =
 * on). The three layers sit side by side and so do the three flag words. */
#ifndef GODHAND_MARKPANEL_H
#define GODHAND_MARKPANEL_H

#define MARKPANEL_MARK_NUM    3
#define MARKPANEL_F_START_LIT 0x8000
#define MARKPANEL_F_ON        0x4000

typedef struct MarkPanel {
    char unk000[0x448];
    int layer[MARKPANEL_MARK_NUM];      /* 0x448 scroll layer of each mark */
    char unk454[0x48];
    unsigned short markFlag[MARKPANEL_MARK_NUM]; /* 0x49C */
} MarkPanel;

typedef char MarkPanel_chk_layer[((int)&((MarkPanel *)0)->layer == 0x448) ? 1 : -1];
typedef char MarkPanel_chk_flag[((int)&((MarkPanel *)0)->markFlag == 0x49C) ? 1 : -1];

#endif
