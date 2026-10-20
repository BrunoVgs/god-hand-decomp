/* sn-2.95.3-136: func_00374B70, registers a sound bank in slot `bank`: resolves the header's relative
 * table offsets, attaches and relocates the optional extra block once, then posts command 3. */
#include "godhand/sndBank.h"
typedef struct SndBankExt {
    int unk00;
    char *data;                         /* 0x04 */
    char *data2;                        /* 0x08 */
    unsigned char fixed;                /* 0x0C */
} SndBankExt;

extern SndBankExt *D_00773250[];
extern int func_003758E8(int cmd);

__attribute__((section(".text.func_00374B70")))
void func_00374B70(short bank, SndBankHdr *hdr, int sysMem, int size, SndBankExt *ext)
{
    SndBank *b;
    SndBankCmd *c;
    SndBankExt **e;

    c = &D_0076A880;
    b = &D_0076DF10[bank];
    b->id = hdr->id;
    b->data = (char *)hdr + hdr->dataOfs;
    b->sysMem = sysMem;
    b->size = size;
    if (hdr->tblOfs == 0) {
        b->tbl = 0;
    } else {
        b->tbl = (char *)hdr + hdr->tblOfs;
    }
    b->num = hdr->num;
    if (hdr->tbl2Ofs == 0) {
        b->tbl2 = 0;
    } else {
        b->tbl2 = (char *)hdr + hdr->tbl2Ofs;
    }
    if (hdr->tbl3Ofs == 0) {
        b->tbl3 = 0;
    } else {
        b->tbl3 = (char *)hdr + hdr->tbl3Ofs;
    }
    e = &D_00773250[bank];
    *e = ext;
    if (ext != 0 && ext->fixed == 0) {
        ext->data = ext->data + (int)ext;
        if ((*e)->data2 != 0)
            (*e)->data2 = (*e)->data2 + (int)*e;
        (*e)->fixed = 1;
    }
    c->bank = bank;
    c->id = b->id;
    c->data = b->data;
    c->sysMem = b->sysMem;
    c->size = b->size;
    c->tbl = b->tbl;
    c->num = b->num;
    c->tbl2 = b->tbl2;
    c->tbl3 = b->tbl3;
    func_003758E8(3);
}
