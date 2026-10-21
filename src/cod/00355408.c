__attribute__((section(".text.func_00355408")))
void *func_00355408(char *object, void *key)
{
    char *record;
    char *slot;
    char *cursor;
    int index;
    record = *(char **)(object + 0x1FC0);
    slot = object + 0x16B0;
    cursor = record + 0x180;
    for (index = 0; index < 16; index += 1) {
        if (slot + 8 == key)
            return cursor;
        slot += 0x88;
        cursor += 0xF0;
    }
    return 0;
}
