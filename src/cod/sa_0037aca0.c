/* sn-2.95.3-136: func_0037ACA0, actor update step when the actor is idle. */
extern int IsActorActiveOrReady_379EC0(void *self);
extern void func_0037A1F0(void *self);
extern int func_0037A4C8(void *self);
extern int func_0037AD08(void *self);
extern void func_0037AD88(void *self);
extern void func_0037A298(void *self);

__attribute__((section(".text.func_0037ACA0")))
void func_0037ACA0(void *self)
{
    if (IsActorActiveOrReady_379EC0(self) != 0)
        return;
    func_0037A1F0(self);
    if (func_0037A4C8(self) == 0 && func_0037AD08(self) == 0)
        func_0037AD88(self);
    func_0037A298(self);
}
