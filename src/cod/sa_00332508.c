/* cygnus-2.96, --f=-freorder-blocks: NM closer handoff. */
typedef struct SifRpcClient {
    char unk00[0x24];
    int serve;                  /* 0x24 */
} SifRpcClient;

extern int D_003D84BC;
extern unsigned int D_003D84A4;
extern SifRpcClient D_003D8D40;
extern char D_00454270[];
extern int func_003B2F48(void *cd, unsigned int sid, int mode);
extern void func_003260C8(const char *msg);

__attribute__((section(".text.func_00332508")))
void func_00332508(void)
{
    int i;
    int end;

    if (D_003D84BC == 0) {
        while (1) {
            if (func_003B2F48(&D_003D8D40, D_003D84A4, 0) < 0) {
                func_003260C8(D_00454270);
                while (1) {
                }
            }
            if (D_003D8D40.serve != 0) {
                break;
            }
            end = -1;
            for (i = 0xFFFF; i != end; i -= 4) {
            }
        }
    }
    D_003D84BC++;
}
