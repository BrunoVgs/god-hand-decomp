/* include/godhand/StdString.h - the g++ 2.x libstdc++ string.
 *
 * A string is one pointer to its character data. The reference-counted Rep
 * header sits right in front of the data, so the length lives 16 bytes
 * before `dat`.
 */
#ifndef GODHAND_STDSTRING_H
#define GODHAND_STDSTRING_H

typedef struct StdStringRep {
    unsigned int len;                   /* 0x0 characters, no terminator */
    unsigned int res;                   /* 0x4 capacity */
    unsigned int ref;                   /* 0x8 */
    int selfish;                        /* 0xC */
} StdStringRep;

typedef struct StdString {
    char *dat;
} StdString;

#define STDSTRING_REP(s)  ((StdStringRep *)(s)->dat - 1)

#endif
