typedef struct SfdSync {
    char pad0[0xBB0];
    int audioPos;
    int videoPos;
} SfdSync;

typedef struct SfdSyncCond {
    int pad0;
    int sys;
    int video;
    int audio;
    char pad10[0x10];
    int usr;
} SfdSyncCond;

extern void Obj35C0_Set_a1_0_a2_C140(SfdSync *sfd, int a, int b);
extern void func_0035BEF0(SfdSync *sfd, SfdSyncCond *c);
extern void sftrn_BuildVideo(SfdSync *sfd, SfdSyncCond *c);
extern void sftrn_BuildAudio(SfdSync *sfd, SfdSyncCond *c);
extern void sftrn_BuildUsr(SfdSync *sfd, SfdSyncCond *c);
extern void func_0035A000(SfdSync *sfd, int tr, int v);

__attribute__((section(".text.func_0035BDD0")))
int func_0035BDD0(SfdSync *sfd, SfdSyncCond *c)
{
    if (c->sys != 0) {
        Obj35C0_Set_a1_0_a2_C140(sfd, 0, 0);
        func_0035BEF0(sfd, c);
    } else if (c->video != 0) {
        Obj35C0_Set_a1_0_a2_C140(sfd, 0, 1);
        sftrn_BuildVideo(sfd, c);
        func_0035A000(sfd, 6, 0);
        sfd->videoPos = 0;
    } else if (c->audio != 0) {
        Obj35C0_Set_a1_0_a2_C140(sfd, 0, 2);
        sftrn_BuildAudio(sfd, c);
        func_0035A000(sfd, 5, 0);
        sfd->audioPos = 0;
    } else if (c->usr != 0) {
        Obj35C0_Set_a1_0_a2_C140(sfd, 0, 7);
        sftrn_BuildUsr(sfd, c);
        func_0035A000(sfd, 6, 0);
        func_0035A000(sfd, 5, 0);
        sfd->videoPos = 0;
        sfd->audioPos = 0;
    } else {
        return -1;
    }
    return 0;
}
