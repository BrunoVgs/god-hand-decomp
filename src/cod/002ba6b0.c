typedef struct {
    char pad[0x20];
    short delta;
    short index;
    float (*function)(char *);
} PhaseAVtSlot;

extern char D_005FEE00[];

__attribute__((section(".text.func_002BA6B0")))
void func_002BA6B0(char *self)
{
    PhaseAVtSlot *object = *(PhaseAVtSlot **)(self + 0x100);
    *(float *)(self + 0xE4) =
        object->function(self + object->delta);
}
