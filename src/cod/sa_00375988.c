/* sn-2.95.3-136: func_00375988, registers a sound bank header in slot `bank` and posts command 6. */
typedef struct BankHdr375988 {
    int id;                     /* 0x00 */
    int dataOfs;                /* 0x04 */
    int unk08;
    int unk0C;
    int tblOfs;                 /* 0x10 */
    int num;                    /* 0x14 */
    int tbl2Ofs;                /* 0x18 */
    int tbl3Ofs;                /* 0x1C */
} BankHdr375988;

typedef struct Bank375988 {
    int id;                     /* 0x00 */
    char *data;                 /* 0x04 */
    int sysMem;                 /* 0x08 */
    int size;                   /* 0x0C */
    char *tbl;                  /* 0x10 */
    int num;                    /* 0x14 */
    char *tbl2;                 /* 0x18 */
    char *tbl3;                 /* 0x1C */
} Bank375988;

typedef struct Cmd76A880 {
    int unk00;
    int bank;                   /* 0x04 */
    int id;                     /* 0x08 */
    char *data;                 /* 0x0C */
    int sysMem;                 /* 0x10 */
    int size;                   /* 0x14 */
    char *tbl;                  /* 0x18 */
    int num;                    /* 0x1C */
    char *tbl2;                 /* 0x20 */
    char *tbl3;                 /* 0x24 */
} Cmd76A880;

extern Bank375988 D_0076EA50[];
extern Cmd76A880 D_0076A880;
extern int func_003758E8(int cmd);

__attribute__((section(".text.func_00375988")))
void func_00375988(short bank, BankHdr375988 *hdr, int sysMem, int size)
{
    Bank375988 *b;
    Cmd76A880 *c;

    c = &D_0076A880;
    b = &D_0076EA50[bank];
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
    c->bank = bank;
    c->id = b->id;
    c->data = b->data;
    c->sysMem = b->sysMem;
    c->size = b->size;
    c->tbl = b->tbl;
    c->num = b->num;
    c->tbl2 = b->tbl2;
    c->tbl3 = b->tbl3;
    func_003758E8(6);
}
