/* terminate / unexpected (libgcc exception.cc): call the installed handler, never return. */

#include "godhand/eh.h"

__attribute__((section(".text.terminate")))
void terminate(void)
{
    D_003C4908();
}

__attribute__((section(".text.unexpected")))
void unexpected(void)
{
    D_003C4F00();
}
