/* sn-2.95.3-136 matched 72-byte Phase A functions. */

extern float fRand1_1(void);
extern float func_0031D108(unsigned int *);
extern int func_00306A08(void *, void *, void *);
extern char *func_003A93A8(void *, int);
extern int func_003A5678(void *, void *);

__attribute__((section(".text.frand")))
float frand(float minimum, float maximum)
{
    float half;
    float random;
    half = (maximum - minimum) * 0.5f;
    random = fRand1_1();
    minimum = minimum + half;
    half = half * random;
    return half + minimum;
}

__attribute__((section(".text.func_0031D0C0")))
float func_0031D0C0(unsigned int *seed)
{
    unsigned int value;
    float result;
    value = *seed * 0x19660D + 0x3C6EF35F;
    *seed = value;
    *(unsigned int *)&result = (value & 0x7FFFFF) | 0x3F800000;
    return result - 1.0f;
}

__attribute__((section(".text.func_0031D168")))
float func_0031D168(unsigned int *seed, float minimum, float maximum)
{
    float half;
    float random;
    half = (maximum - minimum) * 0.5f;
    random = func_0031D108(seed);
    minimum = minimum + half;
    half = half * random;
    return half + minimum;
}

__attribute__((section(".text.func_00306CC8")))
int func_00306CC8(
    void **table, unsigned int index, void *argument, int *output)
{
    void **slot;
    *output = 0;
    if (index >= 0x40)
        return 0;
    slot = table + index;
    if (*slot == 0)
        return 0;
    return func_00306A08(*slot, argument, output) != 0;
}

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
