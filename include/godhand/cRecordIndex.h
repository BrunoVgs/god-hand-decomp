/* include/godhand/cRecordIndex.h - a pool of 0x24-byte records addressed
 * through a byte index.
 *
 * The object at D_005FEC58 holds a pointer to a table of records, a record
 * count and a byte array at +0x14 that maps an index to a record number.
 * func_002C9008 reads it and the skill-slot helpers around 0x002C9AD0 read
 * the same byte array to get a skill id. Field names are ours, taken from
 * the methods that touch them; unkNNN stays where nobody has named a field.
 */
#ifndef GODHAND_CRECORDINDEX_H
#define GODHAND_CRECORDINDEX_H

#define RECORDINDEX_RECORD_SIZE 0x24

typedef struct cRecordIndex {
    void *table;                    /* 0x00 first record, null while unloaded */
    int unk04;                      /* 0x04 */
    int unk08;                      /* 0x08 */
    unsigned int count;             /* 0x0C number of valid indexes */
    int limit;                      /* 0x10 highest index the caller may ask for */
    signed char index[1];           /* 0x14 index -> record number (or skill id) */
} cRecordIndex;

#endif
