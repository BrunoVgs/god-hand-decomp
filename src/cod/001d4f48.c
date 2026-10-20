typedef struct {
    char pad[0x98];
    int f98;
    int f9C;
} PhaseAObj98;

extern char D_005FEE00[];
extern int cIDBase_release(void *);
extern PhaseAObj98 **D_003C2384;

__attribute__((section(".text.func_001D4F48")))
void func_001D4F48(char *self)
{
    PhaseAObj98 *object;
    cIDBase_release(self + 0x10);
    object = *D_003C2384;
    object->f9C = 0;
    object->f98 = 0;
}
