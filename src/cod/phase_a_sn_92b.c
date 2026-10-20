/* sn-2.95.3-136 matched 92-byte array scans.
 * count = i after the limit copy keeps the count in a0 long enough
 * to be moved into the loop bound, then dies. */
__attribute__((section(".text.func_003827F0")))
int func_003827F0(int unused, unsigned char *obj)
{
    int count = *(int *)(obj + 0x38);
    int limit;
    int i = 0;
    unsigned char key;
    unsigned char *base;

    if (count <= 0)
        goto done;
    key = obj[2];
    limit = count;
    count = i;
    base = obj + 0x48;
    do {
        int next = i + 1;
        if (i == (int)key - 1)
            goto advance;
        if (base[next] == base[key])
            goto advance;
        return 0;
    advance:
        i = next;
    } while (i < limit);
done:
    return 1;
}

__attribute__((section(".text.func_00384138")))
int func_00384138(int unused, unsigned char *obj)
{
    int count = *(int *)(obj + 0xAC);
    int limit;
    int i = 0;
    unsigned char key;
    unsigned char *base;

    if (count <= 0)
        goto done;
    key = obj[4];
    limit = count;
    count = i;
    base = obj + 0xBC;
    do {
        int next = i + 1;
        if (i == (int)key - 1)
            goto advance;
        if (base[next] == base[key])
            goto advance;
        return 0;
    advance:
        i = next;
    } while (i < limit);
done:
    return 1;
}
