#include "godhand/cScenario.h"
extern void *func_003A52F0(void *, int, int);

__attribute__((section(".text.cScenario_clearTaskData")))
void cScenario_clearTaskData(cScenario *scenario, int index)
{
    if (index >= 0)
        func_003A52F0(&scenario->taskData[index], 0, 8);
}
