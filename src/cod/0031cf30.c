extern float func_0031CF78(void);

__attribute__((section(".text.func_0031CF30")))
float func_0031CF30(void)
{
    float result = func_0031CF78();
    if (result <= 0.0f)
        result = result + 1.0f;
    return result;
}
