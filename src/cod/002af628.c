/* cygnus-2.96 matched TU. */

extern int func_00366918(int, int, int, int);

__attribute__((section(".text.func_002B45E8")))
void func_002B45E8(void) {
}

__attribute__((section(".text.cSceAtManager_getUnitList")))
void *cSceAtManager_getUnitList(void *a0) {
    return (char *)a0 + 0x5C;
}

__attribute__((section(".text.func_0032F570")))
int func_0032F570(void *a0) {
    return *(int *)((char *)a0 + 0x1958);
}

__attribute__((section(".text.func_0035AEC8")))
int func_0035AEC8(int a0, int a1, int a2, int a3) {
    return func_00366918(a0, a1, a2, a3);
}

__attribute__((section(".text.cMessDrawFont_setBodyData")))
void cMessDrawFont_setBodyData(void *a0, void *a1, void *a2, void *a3) {
    *(void **)((char *)a0 + 0x4) = a1;
    *(void **)((char *)a0 + 0xC) = a2;
    *(void **)((char *)a0 + 0x10) = a3;
}
