typedef struct {
    char pad[0xA6];
    unsigned short a6;
    unsigned short a8;
    char mid[4];
    unsigned short ae;
    unsigned short b0;
} PhaseAPanel;

extern char D_005FEE00[];
extern void func_002B1C80(void *);

__attribute__((section(".text.func_002B17F8")))
void func_002B17F8(PhaseAPanel *panel)
{
    panel->ae = panel->a6;
    panel->b0 = panel->a8;
    func_002B1C80(panel);
}
