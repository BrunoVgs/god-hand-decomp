/* cygnus-2.96 (drop-reorder): drops one reference and calls the release hook when the count reaches zero. */
typedef struct Obj348 {
    int f00;
    void (*release)(struct Obj348 *o);
} Obj348;

typedef struct {
    int f00;
    int refs;
} Ref348;

extern Ref348 *Obj0000_Get_Ptr_D_003EE088_Scaled_8_348920(void *key);
extern Obj348 *func_00348938(void *key);

__attribute__((section(".text.func_003482C8")))
void func_003482C8(void *key)
{
    Ref348 *r = Obj0000_Get_Ptr_D_003EE088_Scaled_8_348920(key);
    Obj348 *o = func_00348938(key);

    if (o != 0 && r->refs != 0) {
        if (--r->refs == 0) {
            if (o->release != 0) {
                o->release(o);
            }
        }
    }
}
