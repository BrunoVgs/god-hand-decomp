typedef struct {
    char raw[0x58];
} EntTableSlot;

typedef struct {
    EntTableSlot *items;
} EntTableRef;

extern void func_002D5788(void *, int);

__attribute__((section(".text.func_002D51C0")))
void func_002D51C0(EntTableRef *parent, int index, int value)
{
    func_002D5788(&parent->items[index], value);
}
