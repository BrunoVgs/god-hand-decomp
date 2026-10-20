extern char D_005FEE00[];
extern int BuildSoundEvent_375BF0(void *);

__attribute__((section(".text.func_0037A668")))
void func_0037A668(char *object)
{
    char *entry = object + 0x12C;
    if (entry[7] < 0x29)
        *(int *)(object + 0xC) = BuildSoundEvent_375BF0(entry);
}
