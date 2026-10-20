/* sn-2.95.3-136, call_loop_pad: NM closer handoff. */
/* sn-2.95.3-136: func_00376A90, split from src/cod/batch29_nm.c by the NM closer. */
extern char D_00770850[];

__attribute__((section(".text.func_00376A90")))
void *func_00376A90(int key)
{
    int i;

    for (i = 0; i < 0x30; i++) {
        char *p = D_00770850 + i * 0xE0;
        if (*(unsigned short *)p != 0) {
            if (key == 0)
                return p;
            if (*(int *)(p + 4) == key)
                return p;
        }
    }
    return 0;
}
