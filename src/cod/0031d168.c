extern float func_0031D108(unsigned int *);

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
