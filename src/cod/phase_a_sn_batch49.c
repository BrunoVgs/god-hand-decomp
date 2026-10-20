/* Batch 49: unique SN ~160–172 (scratch-only). */

extern int GuardedCall_00329FD0_329F98(void *p);
extern int func_0032A4A8(void *p);
extern int func_0032A530(void *p);
extern int func_0032A5B8(void *p);
extern int func_0032A648(void *p);
extern void func_00380EB0(void *a0, void *a1, void *a2);
extern int func_00380870(void *p);

__attribute__((section(".text.func_0037FAC8")))
void func_0037FAC8(char *self)
{
    int v1 = 0x48;
    char *s2 = self;
    unsigned char idx;
    int v0;
    char *s1;
    char *s0;

    idx = *(unsigned char *)(s2 + 5);
    v0 = (int)idx * v1;
    v0 = v0 + 0x48;
    s1 = s2 + v0;
    s0 = s1 + 0x10;
    v0 = GuardedCall_00329FD0_329F98(*(void **)(s0 + 0x30));
    if (v0 < 2)
        return;
    v0 = func_0032A4A8(*(void **)(s0 + 0x30));
    *(int *)(s1 + 0x10) = v0;
    v0 = func_0032A530(*(void **)(s0 + 0x30));
    {
        void *p = *(void **)(s0 + 0x30);
        *(int *)(s0 + 4) = v0;
        v0 = func_0032A5B8(p);
    }
    {
        void *p = *(void **)(s0 + 0x30);
        *(int *)(s0 + 8) = v0;
        v0 = func_0032A648(p);
    }
    *(int *)(s0 + 0xC) = v0;
    func_00380EB0(s2, s0, s1);
    *(unsigned char *)(s2 + 2) = 1;
}

__attribute__((section(".text.func_0037FF98")))
void func_0037FF98(char *self)
{
    char *s1 = self;
    char *s0 = s1 + 0x4BC;
    char *s2 = s1 + 0x470;
    int v0;
    int v1;
    void *p;

    v0 = GuardedCall_00329FD0_329F98(*(void **)(s0 + 0x30));
    if (v0 < 2)
        return;
    v0 = func_0032A4A8(*(void **)(s0 + 0x30));
    *(int *)(s1 + 0x4BC) = v0;
    v0 = func_0032A530(*(void **)(s0 + 0x30));
    p = *(void **)(s0 + 0x30);
    *(int *)(s0 + 4) = v0;
    v0 = func_0032A5B8(p);
    p = *(void **)(s0 + 0x30);
    *(int *)(s0 + 8) = v0;
    v0 = func_0032A648(p);
    *(int *)(s0 + 0xC) = v0;
    func_00380EB0(s1, s0, s2);
    v0 = *(int *)(s2 + 0x84);
    v1 = *(int *)(v0 + 4);
    *(int *)(s2 + 0x10) = v1;
    v0 = func_00380870((void *)v1);
    *(int *)(s2 + 0x10) = v0;
    *(unsigned char *)(s1 + 2) = 1;
}
