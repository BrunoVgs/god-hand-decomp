/* sn-2.95.3-136: func_00374B70, registers a sound bank in slot `bank`: resolves the header's relative
 * table offsets, attaches and relocates the optional extra block once, then posts command 3. */
typedef struct BankHdr374B70 {
    int id;                             /* 0x00 */
    int dataOfs;                        /* 0x04 */
    int unk08;
    int unk0C;
    int tblOfs;                         /* 0x10 */
    int num;                            /* 0x14 */
    int tbl2Ofs;                        /* 0x18 */
    int tbl3Ofs;                        /* 0x1C */
} BankHdr374B70;

typedef struct Bank374B70 {
    int id;                             /* 0x00 */
    char *data;                         /* 0x04 */
    int sysMem;                         /* 0x08 */
    int size;                           /* 0x0C */
    char *tbl;                          /* 0x10 */
    int num;                            /* 0x14 */
    char *tbl2;                         /* 0x18 */
    char *tbl3;                         /* 0x1C */
} Bank374B70;

typedef struct Ext374B70 {
    int unk00;
    char *data;                         /* 0x04 */
    char *data2;                        /* 0x08 */
    unsigned char fixed;                /* 0x0C */
} Ext374B70;

typedef struct Cmd374B70 {
    int unk00;
    int bank;                           /* 0x04 */
    int id;                             /* 0x08 */
    char *data;                         /* 0x0C */
    int sysMem;                         /* 0x10 */
    int size;                           /* 0x14 */
    char *tbl;                          /* 0x18 */
    int num;                            /* 0x1C */
    char *tbl2;                         /* 0x20 */
    char *tbl3;                         /* 0x24 */
} Cmd374B70;

extern Bank374B70 D_0076DF10[];
extern Ext374B70 *D_00773250[];
extern Cmd374B70 D_0076A880;
extern int func_003758E8(int cmd);

__attribute__((section(".text.func_00374B70")))
void func_00374B70(short bank, BankHdr374B70 *hdr, int sysMem, int size, Ext374B70 *ext)
{
    Bank374B70 *b;
    Cmd374B70 *c;
    Ext374B70 **e;

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
