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
