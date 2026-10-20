/* cygnus-2.96 */

extern void func_00348E18(void *);
extern void func_00348F68(void *);

__attribute__((section(".text.func_00348DD8")))
void func_00348DD8(char *object)
{
    int *state = (int *)(object + 0x2A4);
    if (*(int *)(object + 0x284) == 1 || *state == 1)
        func_00348E18(object);
    else
        func_00348F68(object);
}
