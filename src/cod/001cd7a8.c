__attribute__((section(".text.func_001CD7A8")))
void func_001CD7A8(char *self)
{
    char *other = *(char **)(self + 0x670);
    float *dst;
    float *src;

    if (other == 0)
        return;
    src = *(float **)(other + 0xF0);
    dst = *(float **)(self + 0xF0);
    if (dst != src) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
    }
    (*(float **)(self + 0xF0))[1] -= 0.6f;
}
