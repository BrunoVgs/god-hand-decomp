extern char D_005FEE00[];
extern void cHeap_free(void *heap, void *p);

__attribute__((section(".text.func_0031C928")))
void func_0031C928(void *block, void *heap)
{
    if (block != 0)
        cHeap_free(heap, block);
}
