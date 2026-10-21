/* sn-2.95.3-136: linear search for *val in [first, last), unrolled by four. */

__attribute__((section(".text.func_00312DB8")))
int *func_00312DB8(int *first, int *last, int *val) {
    int trip;

    for (trip = (last - first) >> 2; trip > 0; trip--) {
        if (*first == *val) return first;
        first++;
        if (*first == *val) return first;
        first++;
        if (*first == *val) return first;
        first++;
        if (*first == *val) return first;
        first++;
    }
    switch (last - first) {
    case 3:
        if (*first == *val) return first;
        first++;
    case 2:
        if (*first == *val) return first;
        first++;
    case 1:
        if (*first == *val) return first;
        first++;
    case 0:
    default:
        return last;
    }
}

