extern char D_005FEE00[];

__attribute__((section(".text.func_00378070")))
void func_00378070(short *values)
{
    int result = values[0] + values[2];
    if (values[2] > 0)
        result = values[1] < result ? values[1] : result;
    else
        result = result < values[1] ? values[1] : result;
    values[0] = result;
    ((unsigned short *)values)[3]++;
}
