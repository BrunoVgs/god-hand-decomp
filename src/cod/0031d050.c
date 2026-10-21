extern float fRand1_1(void);

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
