/* sn-2.95.3-136 matched TU. */

/* A wobble effect record: three oscillators, each with an amplitude, an output, an angle and an angle step. */
typedef struct EspWobble {
    char unk000[0x2B0];
    float amp0;                         /* 0x2B0 */
    float amp1;                         /* 0x2B4 */
    float out0;                         /* 0x2B8 */
    float out1;                         /* 0x2BC */
    float ang0;                         /* 0x2C0 */
    float ang1;                         /* 0x2C4 */
    float step0;                        /* 0x2C8 */
    float step1;                        /* 0x2CC */
    float amp2;                         /* 0x2D0 */
    float out2;                         /* 0x2D4 */
    float ang2;                         /* 0x2D8 */
    float step2;                        /* 0x2DC */
} EspWobble;

extern void func_002FBED0(EspWobble *self);
extern float capVu0Sin(float x);
extern float capVu0Cos(float x);
extern float Adjust_theta(float x);

/* Steps the three oscillators: the first uses sine, the other two cosine; an oscillator with a zero step is left alone. */
__attribute__((section(".text.EspWobble_step")))
void EspWobble_step(EspWobble *self) {
    func_002FBED0(self);
    if (self->step0 != 0.0f) {
        self->out0 = self->amp0 * capVu0Sin(self->ang0);
        self->ang0 = self->ang0 + self->step0;
        self->ang0 = Adjust_theta(self->ang0);
    }
    if (self->step1 != 0.0f) {
        self->out1 = self->amp1 * capVu0Cos(self->ang1);
        self->ang1 = self->ang1 + self->step1;
        self->ang1 = Adjust_theta(self->ang1);
    }
    if (self->step2 != 0.0f) {
        self->out2 = self->amp2 * capVu0Cos(self->ang2);
        self->ang2 = self->ang2 + self->step2;
        self->ang2 = Adjust_theta(self->ang2);
    }
}
