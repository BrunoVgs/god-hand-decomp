typedef struct {
    char pad[0x84];
    int id;
} PhaseAInner84;

typedef struct {
    PhaseAInner84 *p;
} PhaseAOuter84;

extern char D_005FEE00[];
extern int func_003244C8(int);

__attribute__((section(".text.func_002018D0")))
int func_002018D0(PhaseAOuter84 *outer)
{
    return func_003244C8(outer->p->id);
}
