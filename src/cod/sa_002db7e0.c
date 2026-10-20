/* sn-2.95.3-136, as=sn: NM closer handoff. */
extern char *Getplayer(void);
extern float capVu0MagnitudeSqXZ(void *a0, void *a1);
extern float Turn_dest(void *a0, void *a1, float f12, float f13);

__attribute__((section(".text.func_002DB7E0")))
int func_002DB7E0(void *pos)
{
    char *pl = Getplayer();
    float d = capVu0MagnitudeSqXZ(*(void **)(pl + 0xF0), pos);
    float a;
    float t;

    if (d > 2.0f) {
        return 0;
    }
    if (d < 0.5f) {
        return 1;
    }
    a = Turn_dest(*(void **)(pl + 0xF0), pos, *(float *)(pl + 0x104), 3.1415927f);
    if (a < 0.0f) {
        t = -a;
    } else {
        t = a;
    }
    a = t;
    return a < 0.2617994f;
}
