typedef struct {
    char pad[0x84];
    int id;
} StmIdObj;

typedef struct {
    StmIdObj *p;
} StmIdRef;

extern int func_003244C8(int);

__attribute__((section(".text.func_002018D0")))
int func_002018D0(StmIdRef *outer)
{
    return func_003244C8(outer->p->id);
}
