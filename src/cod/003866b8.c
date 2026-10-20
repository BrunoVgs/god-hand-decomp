extern char *func_003A93A8(void *, int);
extern int func_003A5678(void *, void *);

__attribute__((section(".text.func_003866B8")))
int func_003866B8(void *unused, void *name, void *context)
{
    char *text;
    (void)unused;
    text = func_003A93A8(name, 0x2E);
    if (text == 0)
        return 0;
    return func_003A5678(text + 1, context) == 0;
}
