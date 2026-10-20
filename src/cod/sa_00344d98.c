/* cygnus-2.96: func_00344D98, look up the payload of the source block at +0x38 into dst +0x88/+0x8C. */
typedef struct {
    char *data;
    int size;
} Blk344;

extern void func_00360878(char *data, int size, int *out, int *outLen);

__attribute__((section(".text.func_00344D98")))
void func_00344D98(void *unused, char *src, char *dst)
{
    int ptr = 0;
    Blk344 *b = *(Blk344 **)(src + 0x38);
    int size = b->size;
    char *data = b->data;
    int len = 0;

    *(int *)(dst + 0x88) = 0;
    *(int *)(dst + 0x8C) = 0;
    if (data != 0 && size >= 5)
        func_00360878(data + 4, size - 4, &ptr, &len);
    if (ptr != 0 && len > 0) {
        *(int *)(dst + 0x88) = ptr;
        *(int *)(dst + 0x8C) = len;
    }
}
