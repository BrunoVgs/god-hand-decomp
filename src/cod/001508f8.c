/* sn-2.95.3-136 matched TU. */

extern void *func_002D5070(void *a0);

#define ENTRY_TABLE_OFS     0x3DC88     /* first entry in the owner */
#define ENTRY_SIZE          16          /* two 8-byte halves */
#define ENTRY_LAST_INDEX    0x1C1       /* 0x1C2 entries */
#define ENTRY_HALF_SIZE     8
#define OWNER_STATE_RESET   0x2600

/* Runs func_002D5070 on both eight-byte halves of every table entry, then resets the header words and returns self. */
__attribute__((section(".text.EntryTable_constructPairs")))
char *EntryTable_constructPairs(char *self) {
    char *entry = self + ENTRY_TABLE_OFS;
    int i = ENTRY_LAST_INDEX;
    do {
        char *p = entry;
        int j = 1;
        do {
            func_002D5070(p);
            p += ENTRY_HALF_SIZE;
        } while (--j != -1);
        entry += ENTRY_SIZE;
    } while (--i != -1);
    *(int *)(self + 8) = OWNER_STATE_RESET;
    *(int *)(self + 0) = 0;
    *(int *)(self + 0xC) = 0;
    *(int *)(self + 4) = 0;
    return self;
}
