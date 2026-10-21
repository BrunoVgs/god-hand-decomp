/* include/godhand/sndBank.h - sound bank registration (sn code at 0x374B70 and 0x375988).
 *
 * Field names are ours; offsets are exact.
 */
#ifndef GODHAND_SNDBANK_H
#define GODHAND_SNDBANK_H

/* A bank file header. The offsets are from the header. */
typedef struct SndBankHdr {
    int id;                     /* 0x00 */
    int dataOfs;                /* 0x04 */
    int unk08;
    int unk0C;
    int tblOfs;                 /* 0x10 */
    int num;                    /* 0x14 */
    int tbl2Ofs;                /* 0x18 */
    int tbl3Ofs;                /* 0x1C */
} SndBankHdr;

/* A registered bank slot: the header with its offsets resolved. */
typedef struct SndBank {
    int id;                     /* 0x00 */
    char *data;                 /* 0x04 */
    int sysMem;                 /* 0x08 */
    int size;                   /* 0x0C */
    char *tbl;                  /* 0x10 */
    int num;                    /* 0x14 */
    char *tbl2;                 /* 0x18 */
    char *tbl3;                 /* 0x1C */
} SndBank;

/* The bank tables: two bank sets with 48 slots, and a third set read the same way. */
extern SndBank D_0076DF10[];
extern SndBank D_0076E510[];
extern SndBank D_0076EA50[];

/* The command record posted to the sound driver for a bank (D_0076A880). */
typedef struct SndBankCmd {
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
} SndBankCmd;

extern SndBankCmd D_0076A880;

#endif /* GODHAND_SNDBANK_H */
