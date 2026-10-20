typedef struct {
    char pad[0x112];
    unsigned short messNo;
} PhaseAMessageScenario;

extern char D_005FEE00[];
extern int D_003C23A4;
extern int cMessage_ckMessage(int, int);

__attribute__((section(".text.cScenario_isMessOn")))
int cScenario_isMessOn(PhaseAMessageScenario *self)
{
    if (self->messNo == 0xFFFF)
        return 0;
    return cMessage_ckMessage(D_003C23A4, self->messNo);
}
