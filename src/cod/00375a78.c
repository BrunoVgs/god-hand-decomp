typedef struct {
    char bytes[32];
} PhaseASlot32;

extern char D_005FEE00[];
extern void *func_003A52F0(void *, int, int);
extern PhaseASlot32 D_0076EA50[];

__attribute__((section(".text.func_00375A78")))
void func_00375A78(short index)
{
    func_003A52F0(&D_0076EA50[index], 0, 32);
}
