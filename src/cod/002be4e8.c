extern char D_005FEE00[];
extern void cHeap_free();

__attribute__((section(".text.func_002BE4E8")))
void func_002BE4E8(char *object)
{
    void *block = *(void **)(object + 0x4C0);
    if (block != 0)
        cHeap_free(*(int *)((char *)block - 0x20), block);
}
