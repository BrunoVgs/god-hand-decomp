typedef struct {
    int f0;
    unsigned char f4;
} ReleaseEnt;

extern int func_002BE6C8(void *);

__attribute__((section(".text.func_002BE670")))
void func_002BE670(ReleaseEnt *entry)
{
    func_002BE6C8(entry);
    entry->f4 = 0;
    entry->f0 = 0;
}
