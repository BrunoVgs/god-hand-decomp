/* sn-2.95.3-136: func_0037B660, per-frame actor update: a paused actor just toggles its blink
 * phase; otherwise dispatches to the special-state handlers or runs the normal update. */
typedef struct {
    char pad0[0x27];
    unsigned char blink; /* 0x27 */
    unsigned char blinkcnt; /* 0x28 */
    char pad29[0x34 - 0x29];
    int state; /* 0x34 */
    int flags; /* 0x38 */
} BlinkActor;
extern void func_0037B720(BlinkActor *a);
extern void func_0037B768(BlinkActor *a);
extern int IsActorActiveOrReady_379EC0(BlinkActor *a);
extern void func_0037A1F0(BlinkActor *a);
extern int func_0037A4C8(BlinkActor *a);
extern int func_0037B798(BlinkActor *a);
extern int func_0037B808(BlinkActor *a);
extern void func_0037A298(BlinkActor *a);

__attribute__((section(".text.func_0037B660")))
void func_0037B660(BlinkActor *a)
{
    int state;

    if (a->flags & 4) {
        a->blinkcnt = 0;
        a->blink ^= 1;
        return;
    }
    state = a->state;
    if (state & 0x10) {
        func_0037B720(a);
        return;
    }
    if (state & 0x80) {
        func_0037B768(a);
        return;
    }
    if (IsActorActiveOrReady_379EC0(a) != 0)
        return;
    func_0037A1F0(a);
    if (func_0037A4C8(a) == 0 && func_0037B798(a) == 0)
        func_0037B808(a);
    func_0037A298(a);
}
