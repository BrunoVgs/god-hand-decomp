/* sce302_libmpeg :: _sceMpegGetBits. */

extern void _waitIpuIdle(void *);
extern long long _sceMpegWaitIpuIdle64(void *);

__attribute__((section(".text.func_0039EAA8")))
unsigned int func_0039EAA8(void *a0, int n)
{
    unsigned int bits;
    unsigned int cmd;
    unsigned int op;

    _waitIpuIdle(a0);
    if (*(int *)((char *)a0 + 0x828) != 0 || *(int *)((char *)a0 + 0x84C) < n) {
        *(volatile int *)0x10002000 = 0x40000000;
        *(int *)((char *)a0 + 0x828) = 0;
        *(int *)((char *)a0 + 0x82C) = 0x40000000;
        *(int *)((char *)a0 + 0x848) = (int)_sceMpegWaitIpuIdle64(a0);
    }
    bits = (unsigned int)*(int *)((char *)a0 + 0x848) >> (0x20 - n);
    cmd = n | 0x40000000;
    *(int *)((char *)a0 + 0x84C) = 0x20;
    *(volatile int *)0x10002000 = cmd;
    op = cmd & 0xF0000000;
    *(int *)((char *)a0 + 0x82C) = op;
    if (op == 0x20000000) {
        *(int *)((char *)a0 + 0x828) = 0;
    } else if (op == 0x30000000) {
        *(int *)((char *)a0 + 0x828) = 0;
    } else if (op == 0x40000000) {
        *(int *)((char *)a0 + 0x828) = 0;
    } else {
        *(int *)((char *)a0 + 0x828) = 1;
    }
    *(int *)((char *)a0 + 0x848) = (int)_sceMpegWaitIpuIdle64(a0);
    return bits;
}
