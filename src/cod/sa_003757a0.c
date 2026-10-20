/* sn-2.95.3-136, call_loop_pad: NM closer handoff. */
/* sn-2.95.3-136: func_003757A0, split from src/cod/batch49_nm.c by the NM closer. */
extern void *Obj0000_Set_Field_80_372C68(void *arg0);

typedef struct { short delta; short index; void (*pfn)(void *, int); } VtEnt3757A0;
typedef struct { char data[0x80]; VtEnt3757A0 *vt; } Node3757A0;
extern Node3757A0 D_0076A600[3];

__attribute__((section(".text.func_003757A0")))
void func_003757A0(int init, int prio)
{
    if (prio == 0xFFFF) {
        if (init) {
            Node3757A0 *p = D_0076A600;
            int i = 2;
            do {
                Obj0000_Set_Field_80_372C68(p);
                p++;
            } while (i-- != 0);
        } else {
            if (D_0076A600 != 0) {
                Node3757A0 *p = D_0076A600 + 3;
                if (p != D_0076A600) {
                    do {
                        p--;
                        p->vt[1].pfn((char *)p + p->vt[1].delta, 0);
                    } while (p != D_0076A600);
                }
            }
        }
    }
}
