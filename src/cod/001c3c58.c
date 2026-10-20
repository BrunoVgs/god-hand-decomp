/* sn-2.95.3-136 matched TU. */

__attribute__((section(".text.func_001C3C58")))
int func_001C3C58(int *state, unsigned int *data) {
    if (data == 0) return 0;
    state[0] = (int)data;
    if (data[0] != 0x534D4F) {
        state[0] = 0;
        return 0;
    }
    if (data[1] == 0) {
        state[0] = 0;
        return 0;
    }
    if (data[2] < 2U)
        state[1] = (int)(data + 3);
    else
        state[1] = (int)(data + 4);
    return 1;
}
