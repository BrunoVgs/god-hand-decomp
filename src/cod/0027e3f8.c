extern int moveMotion(void *);

__attribute__((section(".text.func_0027E3F8")))
void func_0027E3F8(unsigned char *self)
{
    switch (self[0x2F6]) {
    case 0:
        self[0x2F6]++;
    case 1:
        moveMotion(self);
        break;
    }
}
