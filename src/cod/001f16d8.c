/* sn-2.95.3-136 matched TU. */

#include "godhand/cOmBase.h"

extern float Adjust_theta(float f12);
extern float capVu0Sin(float f12);
extern float capVu0Cos(float f12);

/* sn-2.95.3-136, fp_hazard_rules=mtc1 */





extern char *func_001F0498(void *owner, int obj, cVec *pos, float angle);     /* create one piece */

#define RING_NUM      5
#define RING_STEP     72.0f             /* degrees between two pieces */
#define RING_RADIUS   8.0f
#define RING_OBJ      0x3ED
#define DEG_TO_RAD    0.017453292f

/* Place five pieces (object 0x3ED) evenly on a circle of radius 8 around the origin. */
__attribute__((section(".text.func_001F16D8")))
void func_001F16D8(void *self) {
    int i;
    for (i = 0; i < RING_NUM; i++) {
        cVec pos;
        float a = Adjust_theta((float)i * RING_STEP * DEG_TO_RAD);
        float x = capVu0Sin(a) * RING_RADIUS;
        float z = capVu0Cos(a) * RING_RADIUS;
        pos.x = x;
        pos.y = 0.0f;
        pos.z = z;
        pos.w = 1.0f;
        func_001F0498(self, RING_OBJ, &pos, 0.0f);
    }
}

/* sn-2.95.3-136, fp_hazard_rules=mtc1 */





extern char *func_001F0498(void *owner, int obj, cVec *pos, float angle);     /* create one piece */

#define RING_NUM      6
#define RING_STEP     60.0f             /* degrees between two pieces */
#define RING_RADIUS   8.0f
#define RING_OBJ      0x3EC
#define DEG_TO_RAD    0.017453292f

typedef struct RingOwner {
    char unk000[0xC64];
    char *piece[RING_NUM];              /* 0xC64 the pieces placed on the ring */
} RingOwner;

/* Place six pieces (object 0x3EC) evenly on a circle of radius 8 around the origin and keep them in the owner. */
__attribute__((section(".text.func_001F1810")))
void func_001F1810(RingOwner *self) {
    int i;
    for (i = 0; i < RING_NUM; i++) {
        cVec pos;
        float a = Adjust_theta((float)i * RING_STEP * DEG_TO_RAD);
        float x = capVu0Sin(a) * RING_RADIUS;
        float z = capVu0Cos(a) * RING_RADIUS;
        pos.x = x;
        pos.y = 0.0f;
        pos.z = z;
        pos.w = 1.0f;
        self->piece[i] = func_001F0498(self, RING_OBJ, &pos, 0.0f);
    }
}
