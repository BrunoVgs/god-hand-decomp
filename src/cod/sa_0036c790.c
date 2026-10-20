/* cygnus-2.96: func_0036C790, reads back the device status block and counters into the object. */
typedef struct {
    char data[0x80];
} DevStat36C790;

typedef struct {
    char unk0[0x1D0];
    DevStat36C790 stat;                 /* 0x1D0 */
    char unk250[0x58];
    int a;                              /* 0x2A8 */
    int blocks;                         /* 0x2AC */
    char unk2B0[4];
    int d;                              /* 0x2B4 */
    int e;                              /* 0x2B8 */
    int c;                              /* 0x2BC */
    char unk2C0[0xF4];
    int dev;                            /* 0x3B4 */
} DevObj36C790;

extern void func_0036CE68(int dev, DevStat36C790 *stat);
extern void func_0036CE90(int dev, int *a);
extern void func_0036CEB8(int dev, int *b, int *c, int *x);
extern void func_0036CEE0(int dev, int *d, int *e);

__attribute__((section(".text.func_0036C790")))
void func_0036C790(DevObj36C790 *obj)
{
    DevStat36C790 stat;
    int a, b, c, x, d, e;

    func_0036CE68(obj->dev, &stat);
    func_0036CE90(obj->dev, &a);
    func_0036CEB8(obj->dev, &b, &c, &x);
    func_0036CEE0(obj->dev, &d, &e);
    obj->stat = stat;
    obj->a = a;
    obj->blocks = b / 2048;
    obj->c = c;
    obj->d = d;
    obj->e = e;
}
