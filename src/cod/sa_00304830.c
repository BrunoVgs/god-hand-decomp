/* sn-2.95.3-136: func_00304830, damps and accelerates an object's angular velocity by its parameter
 * block, wraps each axis, and adds it to the object's rotation. */
typedef struct AngVelPrm {
    char unk0[0x1C0];
    float damp;     /* 0x1C0 */
    float acc[3];   /* 0x1C4 */
} AngVelPrm;

typedef struct AngVelObj {
    char unk0[0x100];
    AngVelPrm *prm;  /* 0x100 */
    char unk104[0x24];
    float rv[3];        /* 0x128 */
} AngVelObj;

extern void func_002B62F8(float *rot, AngVelObj *o);
extern void func_002B6230(AngVelObj *o, float *rot);
extern float Adjust_theta(float a);
extern void Adjust_theta_vec(float *v);
extern void capVu0AddVectorXYZ(float *d, float *a, float *b);

__attribute__((section(".text.func_00304830")))
void func_00304830(AngVelObj *o)
{
    float rot[4];
    float v[4];
    AngVelPrm *prm;
    float t;
    float *pv;

    func_002B62F8(rot, o);
    prm = o->prm;
    o->rv[0] *= prm->damp;
    o->rv[1] *= prm->damp;
    o->rv[2] *= prm->damp;
    o->rv[0] = Adjust_theta(o->rv[0] + prm->acc[0] * 0.001f);
    o->rv[1] = Adjust_theta(o->rv[1] + o->prm->acc[1] * 0.001f);
    t = Adjust_theta(o->rv[2] + o->prm->acc[2] * 0.001f);
    v[0] = o->rv[0];
    v[1] = o->rv[1];
    v[2] = t;
    pv = v;
    pv[3] = 1.0f;
    o->rv[2] = t;
    capVu0AddVectorXYZ(rot, rot, v);
    Adjust_theta_vec(rot);
    func_002B6230(o, rot);
}
