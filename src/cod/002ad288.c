typedef struct {
    char pad[0x10];
    int f10;
    int f14;
} ResHolder;

extern void __builtin_delete(void *);

__attribute__((section(".text.func_002AD288")))
void func_002AD288(ResHolder *object, int flags)
{
    object->f14 = 0;
    object->f10 = 0;
    if (flags & 1)
        __builtin_delete(object);
}
