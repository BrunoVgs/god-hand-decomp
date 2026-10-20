typedef struct {
    int a;
    int b;
} PhaseATask;

typedef struct {
    char pad[0x54];
    PhaseATask t[1];
} PhaseAScenario;

extern char D_005FEE00[];
extern void *func_003A52F0(void *, int, int);

__attribute__((section(".text.cScenario_clearTaskData")))
void cScenario_clearTaskData(PhaseAScenario *scenario, int index)
{
    if (index >= 0)
        func_003A52F0(&scenario->t[index], 0, 8);
}
