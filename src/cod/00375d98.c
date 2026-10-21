extern int ForwardSoundEventAll_375DE0(short, short);
extern int BuildSoundEventEntry_375E78(int, short, short);

__attribute__((section(".text.func_00375D98")))
void func_00375D98(int target, short a, short b)
{
    if (target == 0)
        ForwardSoundEventAll_375DE0(a, b);
    else
        BuildSoundEventEntry_375E78(target, a, b);
}
