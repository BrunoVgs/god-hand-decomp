/* SN ProDG ee-gcc 2.95.3: func_00306E38, ages the 32 pool entries; an entry that reaches 900 frames
 * is released and freed. */
extern void func_00306ED8(char *pool, unsigned int i);
extern void func_00306F10(char *pool, unsigned int i);

__attribute__((section(".text.func_00306E38")))
void func_00306E38(char *pool)
{
    unsigned int i;
    char **slot = (char **)(pool + 0x300);

    for (i = 0; i < 0x20; i++) {
        char *e = *slot++;

        if (e != 0 && ++*(unsigned short *)(e + 0x12) == 900) {
            func_00306ED8(pool, i);
            func_00306F10(pool, i);
        }
    }
}
