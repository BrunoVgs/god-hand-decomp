/* include/godhand/criFs.h - CRI file-system root and device paths (cygnus code at 0x335248..). */
#ifndef GODHAND_CRIFS_H
#define GODHAND_CRIFS_H

extern char D_003DA398[];         /* root directory path */
extern char D_003DA4A0[];         /* device prefix */
extern const char D_00454A00[];   /* "/" */
extern const char D_00454BB0[];   /* "host:" */

extern char *func_003A57C4(char *dst, const char *src);

/* What the file lookup at 0x333C00 fills in (0x30 bytes). */
typedef struct CriFileStat {
    int unk00;
    int found;                  /* 0x04 nonzero once the file is located */
    char unk08[0x30 - 0x08];
} CriFileStat;

#endif /* GODHAND_CRIFS_H */
