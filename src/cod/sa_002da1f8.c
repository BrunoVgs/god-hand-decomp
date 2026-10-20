static inline float Absf(float x)
{
    if (x > 0.0f)
        return x;
    return -x;
}

__attribute__((section(".text.Turn_dest_dir")))
float Turn_dest_dir(float now, float dest, float spd)
{
    float d = dest - now;
    float s;

    if (d > 3.1415927f) {
        d -= 6.2831855f;
    }
    if (d < -3.1415927f) {
        d += 6.2831855f;
    }
    s = d > 0.0f ? 1.0f : -1.0f;
    if (!(spd < (d > 0.0f ? d : -d))) {
        spd = Absf(d);
    }
    d = spd * s;
    return d;
}
