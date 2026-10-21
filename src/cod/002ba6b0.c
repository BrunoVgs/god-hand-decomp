typedef struct {
    char pad[0x20];
    short delta;
    short index;
    float (*function)(char *);
} FloatGetterVt;


__attribute__((section(".text.func_002BA6B0")))
void func_002BA6B0(char *self)
{
    FloatGetterVt *object = *(FloatGetterVt **)(self + 0x100);
    *(float *)(self + 0xE4) =
        object->function(self + object->delta);
}
