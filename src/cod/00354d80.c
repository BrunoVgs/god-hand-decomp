/* cygnus-2.96: SFD work release hook (0x354D80). */

typedef struct SfdRef {
    void *obj;
} SfdRef;

typedef struct SfdRefView {
    char unk0000[0x1FC0];
    SfdRef *ref;                /* 0x1FC0 */
} SfdRefView;

extern void func_0036A070(void *obj);

__attribute__((section(".text.func_00354D80")))
int func_00354D80(SfdRefView *w)
{
    if (w->ref->obj == 0) return 0;
    func_0036A070(w->ref->obj);
    return 0;
}
