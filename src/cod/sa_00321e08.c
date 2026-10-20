/* ee-2.9-991111: func_00321E08, libgcc frame.c frame_init: counts the object's FDEs, sorts them
 * into a single array and records the covered pc range. */
typedef struct Fde321E08 Fde321E08;

typedef struct Object321E08 {
    void *pc_begin;                     /* 0x00 */
    void *pc_end;                       /* 0x04 */
    Fde321E08 *fde_begin;               /* 0x08 */
    Fde321E08 **fde_array;              /* 0x0C */
    unsigned int count;                 /* 0x10 */
} Object321E08;

typedef struct FdeVector321E08 {
    Fde321E08 **array;
    unsigned int count;
} FdeVector321E08;

typedef struct FdeAccu321E08 {
    FdeVector321E08 linear;
    FdeVector321E08 erratic;
} FdeAccu321E08;

extern void *func_003A7C70(unsigned int n);
extern unsigned int func_00321D38(Fde321E08 *f);
extern void func_00321D80(Fde321E08 *f, FdeAccu321E08 *accu, void **beg_ptr, void **end_ptr);
extern Fde321E08 **func_00321AD0(FdeAccu321E08 *accu, unsigned int count);

static inline void start_fde_sort(FdeAccu321E08 *accu, unsigned int count)
{
    accu->linear.array = (Fde321E08 **)func_003A7C70(sizeof(Fde321E08 *) * count);
    accu->erratic.array = (Fde321E08 **)func_003A7C70(sizeof(Fde321E08 *) * count);
    accu->linear.count = 0;
    accu->erratic.count = 0;
}

__attribute__((section(".text.func_00321E08")))
void func_00321E08(Object321E08 *ob)
{
    unsigned int count;
    FdeAccu321E08 accu;
    void *pc_begin, *pc_end;

    if (ob->fde_array) {
        Fde321E08 **p = ob->fde_array;
        for (count = 0; *p; ++p)
            count += func_00321D38(*p);
    } else
        count = func_00321D38(ob->fde_begin);

    ob->count = count;

    start_fde_sort(&accu, count);
    pc_begin = (void *)(unsigned int)-1;
    pc_end = 0;

    if (ob->fde_array) {
        Fde321E08 **p = ob->fde_array;
        for (; *p; ++p)
            func_00321D80(*p, &accu, &pc_begin, &pc_end);
    } else
        func_00321D80(ob->fde_begin, &accu, &pc_begin, &pc_end);

    ob->fde_array = func_00321AD0(&accu, count);
    ob->pc_begin = pc_begin;
    ob->pc_end = pc_end;
}
