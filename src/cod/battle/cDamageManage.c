/* TU: cDamageManage [battle] - recovered C++ class. */

__attribute__((section(".text.cDamageManage_CreateDamageGive")))
int cDamageManage_CreateDamageGive(int a0, int a1, int a2) {
    int p = func_001FE1E0(a0);
    if (p == 0) return 0;
    if (SetObjTargetAndActivate_1FD2C0(p, a1, a2) == 0) p = 0;
    return p;
}

__attribute__((section(".text.cDamageManage_ReleaseDamageGive")))
int cDamageManage_ReleaseDamageGive(int a0, int a1) {
    if (a1 == 0) {
        return 0;
    }
    cDvd_releaseAll(a1);
    func_001FCDB8(a1);
    return 1;
}
