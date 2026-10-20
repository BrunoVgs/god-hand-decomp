typedef struct {
    char raw[0x58];
} PhaseASlot58;

typedef struct {
    PhaseASlot58 *items;
} PhaseASlotParent;

extern char D_005FEE00[];
extern void func_002D5788(void *, int);

__attribute__((section(".text.func_002D51C0")))
void func_002D51C0(PhaseASlotParent *parent, int index, int value)
{
    func_002D5788(&parent->items[index], value);
}
