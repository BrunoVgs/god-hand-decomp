/* ee-2.9-991111: func_00322030, libgcc frame.c extract_cie_info: parses a CIE's augmentation, alignment
 * factors and return-address column; returns the first instruction byte, or 0 for an unknown augmentation. */
typedef struct Fde322030 {
    unsigned int length;
    int CIE_delta;
} Fde322030;

typedef struct Cie322030 {
    unsigned int length;
    int CIE_id;
    unsigned char version;
    char augmentation[1];
} Cie322030;

typedef struct CieInfo322030 {
    char *augmentation;   /* 0x00 */
    void *eh_ptr;         /* 0x04 */
    int code_align;       /* 0x08 */
    int data_align;       /* 0x0C */
    unsigned int ra_regno; /* 0x10 */
} CieInfo322030;

union Unaligned322030 {
    void *p;
} __attribute__((packed));

extern char D_004512C0[];
extern char D_004512C8[];
extern int func_003A5678(const char *a, const char *b);
extern unsigned int strlen(const char *s);
extern unsigned char *func_00321938(unsigned char *p, int *val);
extern unsigned char *func_00321980(unsigned char *p, int *val);

__attribute__((section(".text.func_00322030")))
void *func_00322030(Fde322030 *f, CieInfo322030 *c)
{
    unsigned char *p;
    int i;

    c->augmentation = ((Cie322030 *)((char *)&f->CIE_delta - f->CIE_delta))->augmentation;

    if (func_003A5678(c->augmentation, D_004512C0) != 0
        && func_003A5678(c->augmentation, D_004512C8) != 0
        && c->augmentation[0] != 'z')
        return 0;

    p = (unsigned char *)c->augmentation + strlen(c->augmentation) + 1;

    if (func_003A5678(c->augmentation, D_004512C8) == 0) {
        c->eh_ptr = ((union Unaligned322030 *)p)->p;
        p += sizeof(void *);
    } else
        c->eh_ptr = 0;

    p = func_00321938(p, &c->code_align);
    p = func_00321980(p, &c->data_align);
    c->ra_regno = *p++;

    if (c->augmentation[0] == 'z') {
        p = func_00321938(p, &i);
        p += i;
    }

    return p;
}
