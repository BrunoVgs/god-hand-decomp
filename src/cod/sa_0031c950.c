/* sn-2.95.3-136, as=sn (ps2eeas keeps the mtc1 hazard nops): one-segment line; retail uses (x0, y0) for both ends. */
extern unsigned int func_0031CA58(unsigned int a0);
extern void Draw_Line_sc(float (*v)[4], int n, unsigned int col, int a3);

__attribute__((section(".text.func_0031C950")))
void func_0031C950(short x0, short y0, short x1, short y1, unsigned int col, unsigned int z)
{
    float v[2][4];

    v[0][0] = x0;
    v[0][1] = y0;
    v[0][2] = z;
    v[0][3] = 1.0f;
    v[1][0] = x0;
    v[1][1] = y0;
    v[1][2] = z;
    v[1][3] = 1.0f;
    Draw_Line_sc(v, 1, func_0031CA58(col), 1);
}
