/* sn-2.95.3-136: model node setup; fills the node's packet data and returns the end of it (0x1485A0). */
#include "godhand/cModel.h"

extern int func_00155138(cModelNode *node);
extern int func_00155248(cModelNode *node);
extern void func_00154A90(cModelNode *node, int buf, int c);
extern void func_00155358(cModelNode *node, int buf, int c);
extern void func_00148F50(cModelNode *node, cMeshData **data, void *box);
extern void func_001490B0(cModelNode *node, cMeshData **data, void *box);

__attribute__((section(".text.func_001485A0")))
int func_001485A0(cModelNode *node, cMeshData *data, int b, int flags, int n, void *box, int buf)
{
    cMeshData *hold[4];
    int big;
    unsigned short num;

    node->unk400 = b;
    node->unk384 = 0;
    node->dispFlags = flags;
    node->tag = 0;
    node->data = data;
    hold[0] = data;
    num = data->num;
    node->meshNum = num;
    big = data->num >= 2;
    if (big) {
        int size = func_00155138(node);
        node->pktBuf = buf;
        func_00154A90(node, buf, 0);
        buf += size;
    } else {
        int size = func_00155248(node);
        node->pktBuf = buf;
        func_00155358(node, buf, 0);
        buf += size;
    }
    if (flags & 0x01000000) {
        func_00148F50(node, hold, box);
    } else {
        func_001490B0(node, hold, box);
    }
    return buf;
}
