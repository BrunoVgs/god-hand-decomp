/* sn-2.95.3-136 matched TU. */

typedef struct Vec3 {
    float x, y, z;
} Vec3;

/* A sub-object record: the byte header, three positions and a float at 0x154. */
typedef struct SubRec {
    unsigned char kind;                 /* 0x00 */
    char unk01;
    unsigned char type;                 /* 0x02 */
    unsigned char arg;                  /* 0x03 */
    char unk04[0x4C];
    Vec3 center;                        /* 0x50 */
    char unk5C[0x34];
    Vec3 low;                           /* 0x90 vertical offset only */
    char unk9C[0x54];
    Vec3 high;                          /* 0xF0 vertical offset only */
    char unkFC[0x58];
    float extra;                        /* 0x154 */
} SubRec;

#define SUBREC_TYPE_DEFAULT 2
#define SUBREC_ARG_DEFAULT  0x10

extern void func_001C7138(SubRec *self);
extern void func_001C7310(SubRec *self);

/* Initialise the record: default type and argument, zero the two offset
 * vectors apart from their height, copy the centre in and run the two setup calls. */
__attribute__((section(".text.func_001C6C30")))
void func_001C6C30(SubRec *self, Vec3 *center, float highY, float lowY, float extra)
{
    Vec3 *lo;
    Vec3 *hi;
    Vec3 *dst;

    self->type = SUBREC_TYPE_DEFAULT;
    self->arg = SUBREC_ARG_DEFAULT;
    self->kind = 0;
    lo = &self->low;
    self->low.x = 0.0f;
    lo->y = lowY;
    lo->z = 0.0f;
    hi = &self->high;
    self->high.x = 0.0f;
    hi->y = highY;
    hi->z = 0.0f;
    dst = &self->center;
    if (dst != center) {
        self->center.x = center->x;
        dst->y = center->y;
        dst->z = center->z;
    }
    self->extra = extra;
    func_001C7138(self);
    func_001C7310(self);
}
