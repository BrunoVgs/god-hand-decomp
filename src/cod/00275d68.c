extern char D_005FEE00[];
extern int Obj0000_Get_Field_1560_Bit0_27DD00(int);

__attribute__((section(".text.func_00275D68")))
int func_00275D68(char *self)
{
    int child;
    if (*(int *)(self + 0x564) != 0x264)
        return 0;
    child = *(int *)(self + 0x740);
    if (child == 0)
        return 0;
    return Obj0000_Get_Field_1560_Bit0_27DD00(child) != 0;
}
