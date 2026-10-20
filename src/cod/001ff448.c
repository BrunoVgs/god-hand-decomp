typedef struct {
    int a;
    int b;
} PhaseAPair;

extern char D_005FEE00[];
extern void cDataSlot_resetSeHandles(void *);

__attribute__((section(".text.func_001FF448")))
void func_001FF448(PhaseAPair *object)
{
    if (object->b >= 0)
        cDataSlot_resetSeHandles(object);
}
