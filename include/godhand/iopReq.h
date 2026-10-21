/* include/godhand/iopReq.h - an IOP request polled by the cygnus code at 0x331310..0x331458.
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_IOPREQ_H
#define GODHAND_IOPREQ_H

typedef struct IopReq {
    char unk00[2];
    signed char state;          /* 0x02 2 while it runs */
    char unk03[0x30 - 0x03];
    int handle;                 /* 0x30 */
    int err;                    /* 0x34 */
} IopReq;

#endif /* GODHAND_IOPREQ_H */
