/* include/godhand/criFs.h - CRI file-system root and device paths (cygnus code at 0x335248..). */
#ifndef GODHAND_CRIFS_H
#define GODHAND_CRIFS_H

extern char D_003DA398[];         /* root directory path */
extern char D_003DA4A0[];         /* device prefix */
extern const char D_00454A00[];   /* "/" */
extern const char D_00454BB0[];   /* "host:" */

extern void func_003A57C4(char *dst, const char *src);

#endif /* GODHAND_CRIFS_H */
