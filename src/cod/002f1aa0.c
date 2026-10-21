typedef struct {
    char bytes[16];
} QWord;

extern QWord D_0061B660;

__attribute__((section(".text.func_002F1AA0")))
void func_002F1AA0(int enabled, unsigned int type)
{
    if (type == 0xFFFF && enabled != 0) {
        __asm__ __volatile__(
            "sqc2 $vf0, %0" : : "m"(D_0061B660) : "memory");
    }
}
