typedef struct {
    char pad0[8];
    int count;
    char padC[0x20 - 0xC];
    int handle;
} Grp3832C8;

typedef struct {
    char pad0[0x30];
    int handle;
} Info3832C8;

typedef struct {
    char pad0[0x1C];
    short x[5];
    short y[5];
    char pad30[4];
    Info3832C8 info;
    char pad68[0xA4 - 0x68];
    Grp3832C8 grp;
} Menu3832C8;

extern int func_0032DCD0(int, int);
extern void func_0032A6D0(int handle, int a1, int a2);

__attribute__((section(".text.func_003832C8")))
void func_003832C8(void *ctl, Menu3832C8 *m, unsigned char multi)
{
    Grp3832C8 *g;
    Info3832C8 *info;
    int i;
    int h;

    if (multi) {
        g = &m->grp;
        for (i = 0; i < g->count; i++) {
            h = func_0032DCD0(g->handle, i);
            func_0032A6D0(h, 0, m->x[i + 1]);
            func_0032A6D0(h, 1, m->y[i + 1]);
        }
    } else {
        info = &m->info;
        func_0032A6D0(info->handle, 0, m->x[0]);
        func_0032A6D0(info->handle, 1, m->y[0]);
    }
}
