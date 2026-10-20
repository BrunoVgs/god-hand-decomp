typedef struct {
    char pad[0x98];
    int f98;
    int f9C;
} IdPickHost;

extern int cIDBase_release(void *);
extern IdPickHost **D_003C2384;

__attribute__((section(".text.func_001D4F48")))
void func_001D4F48(char *self)
{
    IdPickHost *object;
    cIDBase_release(self + 0x10);
    object = *D_003C2384;
    object->f9C = 0;
    object->f98 = 0;
}
