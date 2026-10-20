/* sn-2.95.3-136 matched TU: pack key lookup (0x152340). */

#include "godhand/pack.h"

/* Index of key in the pack's 64-bit key table, which follows the offset
 * table aligned up to 8 bytes; -1 when absent or the pack is not type 3. */
__attribute__((section(".text.func_00152340")))
int func_00152340(Pack *pack, long key)
{
    unsigned int align = 8;
    unsigned int alignMod = 8;
    unsigned int alignPad = 8;
    char *base;
    long *keys;
    int i;

    base = (char *)&pack->ofs[pack->count];
    keys = (long *)(base + (align - (unsigned int)base % alignMod) % alignPad);
    if (func_00151630(pack) != 3) {
        return -1;
    }
    for (i = 0; i < pack->count; i++) {
        if (keys[i] == key) {
            return i;
        }
    }
    return -1;
}
