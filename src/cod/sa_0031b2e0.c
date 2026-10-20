/* sn-2.95.3-136: func_0031B2E0, score how far the angle turned since last frame (45/90/135 degree steps). */
extern float func_002DA940(float a, float b);

typedef struct {
    char pad00[0x78];
    unsigned short on;
    char pad7A[2];
    float ang;
    char pad80[8];
    float prevAng;
    int score;
} TurnScore;

__attribute__((section(".text.func_0031B2E0")))
int func_0031B2E0(void *unused, TurnScore *p)
{
    float d;

    p->score = 0;
    if (p->on != 0) {
        d = func_002DA940(p->prevAng, p->ang);
        if (d > 0.7853982f || d < -0.7853982f) {
            p->score += 2;
        }
        if (d > 1.5707964f || d < -1.5707964f) {
            p->score += 2;
        }
        if (d > 2.3561945f || d < -2.3561945f) {
            p->score += 4;
        }
    }
    p->prevAng = p->ang;
    return p->score;
}
