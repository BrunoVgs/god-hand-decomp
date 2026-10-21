/* include/godhand/cMessage.h - cMessage, the message window manager.
 *
 * The manager keeps a singly linked list of open windows at 0x10. A window
 * starts with its work id (the handle callers hold) and links to the next
 * at 0x08. cMessage_create returns the new window's work id, or
 * CMESSAGE_NONE when no window could be made.
 * Offsets are exact; unknown spans stay unkNNN.
 */
#ifndef GODHAND_CMESSAGE_H
#define GODHAND_CMESSAGE_H

#define CMESSAGE_NONE  0xFFFF

typedef struct cMessageWin {
    unsigned short workId;      /* 0x00 handle returned by create */
    short prio;                 /* 0x02 open list is kept by descending prio */
    struct cMessageWin *prev;   /* 0x04 */
    struct cMessageWin *next;   /* 0x08 */
} cMessageWin;

typedef struct cMessage {
    char unk000[0x10];
    cMessageWin *head;          /* 0x010 open windows */
    cMessageWin *free;          /* 0x014 free windows */
    char unk018[0xBD8 - 0x18];
    unsigned short serial;      /* 0xBD8 */
} cMessage;

extern cMessageWin *func_002B2318(cMessageWin *win);
extern void func_002B2080(cMessageWin *win);
extern void func_002B22E8(cMessageWin *win, cMessageWin *prev, cMessageWin *next, short prio, int serial);

#endif
