extern char D_005FEE00[];
extern void ActorRec_reset(void *);

__attribute__((section(".text.func_001FCDB8")))
void func_001FCDB8(char *self)
{
    ActorRec_reset(self);
    *(int *)(self + 0x34) = 0;
    self[0x49] = 1;
}
