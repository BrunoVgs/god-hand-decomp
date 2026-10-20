/* sn-2.95.3-136, as=sn: NM closer handoff. */
extern char *Getplayer(void);

__attribute__((section(".text.func_00270D00")))
int func_00270D00(char *self)
{
    char *pl = Getplayer();
    float d;
    float t;

    switch (*(int *)(self + 0x564)) {
    case 0x20B:
    case 0x221:
    case 0x242:
        return 0;
    }
    d = (*(float **)(pl + 0xF0))[1] - (*(float **)(self + 0xF0))[1];
    if (d < 0.0f) {
        t = -d;
    } else {
        t = d;
    }
    d = t;
    if (d > 0.1f) {
        return 0;
    }
    return 1;
}
