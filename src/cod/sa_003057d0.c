/* sn-2.95.3-136: NM closer handoff. */
/* sn-2.95.3-136: func_003057D0, split from src/cod/batch44_nm.c by the NM closer. */
extern void func_00305358(void *a0, void *a1);
extern void *SearchData(void *a, void *b, int c);
extern void func_00306AF0(void *a0, int a1, void *a2);
extern char D_00450048[];
extern char D_00741DC8[];

__attribute__((section(".text.func_003057D0")))
void func_003057D0(int *self, int id, void *data)
{
    void *p;

    self[0] = id;
    if (self[3] == 0) {
        func_00305358(self + 1, data);
        p = SearchData(data, D_00450048, 0);
        if (p != 0)
            func_00306AF0(D_00741DC8, id, p);
    }
    self[3]++;
}
