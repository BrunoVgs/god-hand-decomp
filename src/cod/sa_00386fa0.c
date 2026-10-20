/* sn-2.95.3-136: func_00386FA0, queues a copy of a 0x60-byte request in a new node unless the id is
 * already busy or the request is flagged; returns the node's handle. */
typedef struct SndReq {
    char pad0[6];
    unsigned char kind;                 /* 0x06 */
    char pad7[7];
    unsigned short flags;               /* 0x0E */
    char pad10[0x50];
} SndReq;

typedef struct SndReqNode {
    short used;                         /* 0x00 */
    int handle;                         /* 0x04 */
    unsigned char kind;                 /* 0x08 */
    unsigned char state;                /* 0x09 */
    short link;                         /* 0x0A */
    short id;                           /* 0x0C */
    char pad0E[2];
    SndReq req;                      /* 0x10 */
} SndReqNode;

extern int func_00387430(short id);
extern SndReqNode *func_00377998(void);
extern int func_00377FF8(void);

__attribute__((section(".text.func_00386FA0")))
int func_00386FA0(short id, SndReq *req)
{
    SndReqNode *n;

    if (func_00387430(id) != 0)
        return 0;
    if (req->flags & 0x8000)
        return 0;
    n = func_00377998();
    if (n == 0)
        return 0;
    n->used = 1;
    n->handle = func_00377FF8();
    n->kind = req->kind;
    n->state = 2;
    n->link = -1;
    n->id = id;
    n->req = *req;
    return n->handle;
}
