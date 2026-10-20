/* sn-2.95.3-136, as=sn: func_003774A8, run the per-kind update for both active task slots. */
typedef struct TaskEnt {
    unsigned short active;
    char pad02[0x14 - 0x02];
    unsigned short kind;
    char pad16[0xA0 - 0x16];
} TaskEnt;

extern TaskEnt D_0076E910[2];
extern void (*D_003F21A8[])(TaskEnt *e);

__attribute__((section(".text.func_003774A8")))
void func_003774A8(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        if (D_0076E910[i].active)
            D_003F21A8[D_0076E910[i].kind](&D_0076E910[i]);
    }
}
