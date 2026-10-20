/* cygnus-2.96: Sofdec handle destroy, releasing each sub-resource before clearing the handle (0x3443E0). */
typedef struct Obj3443E0 Obj3443E0;

typedef struct Vt3443E0 {
    void *unk00[3];
    void (*destroy)(Obj3443E0 *self);
} Vt3443E0;

struct Obj3443E0 {
    Vt3443E0 *vt;
};

typedef struct Mwsf3443E0 {
    int used;
    char pad004[0x3C - 4];
    void *sfd;
    void *unk40;
    char pad044[4];
    void *unk48;
    char pad04C[0xA8 - 0x4C];
    void *unkA8;
    char pad0AC[0x1C0 - 0xAC];
    Obj3443E0 *unk1C0;
    char pad1C4[0x1E0 - 0x1C4];
    Obj3443E0 *unk1E0;
    char pad1E4[0x284 - 0x1E4];
    char unk284[0x20];
    char unk2A4[0x2C];
    void *unk2D0;
} Mwsf3443E0;

extern char D_004576A0[];
extern void func_003497F8(int on);
extern void func_00345DF0(Mwsf3443E0 *self);
extern void func_00347370(Mwsf3443E0 *self);
extern void Forward35FB88_346C30(void *p);
extern void func_00335500(void *p);
extern void Forward327D90_349AB8(void *p);
extern void func_00342B98(void *p);
extern void MWSFCRE_DestroySfd(void *sfd);
extern void func_00348870(void *p);
extern void func_00344710(Mwsf3443E0 *self);
extern int func_00344790(Mwsf3443E0 *self);
extern void MWSFSVM_Error(char *msg);
extern void func_003A52F0(void *p, int c, int n);

__attribute__((section(".text.func_003443E0")))
void func_003443E0(Mwsf3443E0 *self)
{
    if (self == 0) {
        return;
    }
    func_003497F8(1);
    func_00345DF0(self);
    self->used = 0;
    func_003497F8(0);
    func_00347370(self);
    if (self->unkA8 != 0) {
        Forward35FB88_346C30(self->unkA8);
    }
    if (self->unk48 != 0) {
        func_00335500(self->unk48);
    }
    if (self->unk40 != 0) {
        Forward327D90_349AB8(self->unk40);
    }
    if (self->unk1C0 != 0) {
        self->unk1C0->vt->destroy(self->unk1C0);
    }
    if (self->unk1E0 != 0) {
        self->unk1E0->vt->destroy(self->unk1E0);
    }
    if (self->unk2D0 != 0) {
        func_00342B98(self->unk2D0);
    }
    if (self->sfd != 0) {
        MWSFCRE_DestroySfd(self->sfd);
    }
    func_00348870(self->unk284);
    func_00348870(self->unk2A4);
    func_00344710(self);
    if (func_00344790(self) != 0) {
        MWSFSVM_Error(D_004576A0);
    }
    func_003A52F0(self, 0, 0x304);
    self->used = 0;
}
