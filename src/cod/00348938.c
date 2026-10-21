extern int D_003EE088[];
__attribute__((section(".text.func_00348938")))
int func_00348938(int a0) { return D_003EE088[a0 * 2]; }

__attribute__((section(".text.func_00348950")))
void func_00348950(int value, int index) { D_003EE088[index * 2] = value; }
