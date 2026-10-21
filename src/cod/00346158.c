/* cygnus-2.96 */

extern int Forward328098_349B88(void *);
extern int func_00358F68(void *);

__attribute__((section(".text.func_00346158")))
void func_00346158(char *self)
{
    void *object = *(void **)(self + 0x40);
    void *other = *(void **)(self + 0x3C);
    if (object == 0)
        return;
    if (Forward328098_349B88(object) != 3)
        return;
    func_00358F68(other);
}
