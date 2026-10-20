extern char D_005FEE00[];
extern void moveMotion(void *);

__attribute__((section(".text.func_001CA1F8")))
void func_001CA1F8(unsigned char *self)
{
    switch (self[0x2F6]) {
    case 0:
        self[0x2F6]++;
    case 1:
        moveMotion(self);
        break;
    }
}
