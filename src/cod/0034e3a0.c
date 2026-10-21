/* cygnus-2.96: func_0034E3A0, fetches the current read chunk of the stream; when a new
 * sector-aligned chunk of at least 2 KiB arrives, notifies the read callback once. */
#include "godhand/mwsfd.h"
typedef struct {
    char *ptr; /* 0x0 */
    int len; /* 0x4 */
    int pad8;
    int extra; /* 0xC */
    int pad10[4];
} SfdRdChunk;
extern int func_0034C2B8(SfdHn *hn, void *sj, SfdRdChunk *ck);

__attribute__((section(".text.func_0034E3A0")))
int func_0034E3A0(SfdHn *hn, char **ptr, int *len, int unused, int *end)
{
    SfdRdChunk ck;
    int ret;

    ret = func_0034C2B8(hn, hn->ch.sj, &ck);
    if (ret == 0) {
        *len = ck.len;
        *end = ck.len + ck.extra;
        *ptr = ck.ptr;
        if (*len >= 0x800 && ck.ptr != hn->lastRead && !(hn->readPos & 0x7FF)) {
            void (*cb)(void *, char *, int) = hn->readCb;
            void *obj = hn->readCbObj;
            if (cb != 0)
                cb(obj, ck.ptr, *len);
            hn->lastRead = *ptr;
        }
        return 0;
    }
    return ret;
}
