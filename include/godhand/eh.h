/* include/godhand/eh.h - libgcc exception handler hooks (exception.cc, ee-2.9-991111). */
#ifndef GODHAND_EH_H
#define GODHAND_EH_H

typedef void (*eh_handler)(void) __attribute__((noreturn));

extern eh_handler D_003C4908;           /* __terminate_func */
extern eh_handler D_003C4F00;           /* __unexpected_func */

#endif
