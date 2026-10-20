typedef struct Sfd35BDD0 {
    char pad0[0xBB0];
    int audioPos;
    int videoPos;
} Sfd35BDD0;

typedef struct Cond35BDD0 {
    int pad0;
    int sys;
    int video;
    int audio;
    char pad10[0x10];
    int usr;
} Cond35BDD0;

extern void Obj35C0_Set_a1_0_a2_C140(Sfd35BDD0 *sfd, int a, int b);
extern void func_0035BEF0(Sfd35BDD0 *sfd, Cond35BDD0 *c);
extern void sftrn_BuildVideo(Sfd35BDD0 *sfd, Cond35BDD0 *c);
extern void sftrn_BuildAudio(Sfd35BDD0 *sfd, Cond35BDD0 *c);
extern void sftrn_BuildUsr(Sfd35BDD0 *sfd, Cond35BDD0 *c);
extern void func_0035A000(Sfd35BDD0 *sfd, int tr, int v);

__attribute__((section(".text.func_0035BDD0")))
int func_0035BDD0(Sfd35BDD0 *sfd, Cond35BDD0 *c)
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
