extern int func_003A5148(int, int, int);

__attribute__((section(".text.func_00354430")))
void func_00354430(int *destination, int *source)
{
    func_003A5148(destination[0], source[0], source[1]);
    destination[1] = source[1];
}
