/* cygnus-2.96: func_0035FC88, records the tag chunk at +0x14 of the handle and forwards the found tag to
 * SFXZ_SetTagInf. */
typedef signed char Sint8;
typedef int Sint32;
typedef struct { Sint8 *data; Sint32 len; } SJCK;
typedef struct { Sint8 *data; Sint32 len; } SJTAG;
typedef struct { int set; SJCK ck; } TagRec;
typedef struct {
    char pad0[0x14];
    TagRec rec; /* 0x14 */
    char pad20[4];
    void *sfxz; /* 0x24 */
} TagHn;
extern Sint8 D_0045A050[];
extern Sint8 D_0045A058[];
extern Sint8 *SJ_SearchTag(SJCK *ck, Sint8 *tag, Sint8 *endtag, SJTAG *tagck);
extern int SFXZ_SetTagInf(void *h, int a, int b);

__attribute__((section(".text.func_0035FC88")))
void func_0035FC88(TagHn *hn, Sint8 *data, Sint32 len)
{
    TagRec *rec = &hn->rec;
    SJCK ck;
    SJTAG tag;
    void *sfxz;

    rec->ck.data = data;
    rec->ck.len = len;
    sfxz = hn->sfxz;
    ck.data = data;
    ck.len = len;
    if (SJ_SearchTag(&ck, D_0045A050, D_0045A058, &tag) == 0)
        SFXZ_SetTagInf(sfxz, 0, 0);
    else
        SFXZ_SetTagInf(sfxz, (int)tag.data, tag.len);
    rec->set = 1;
}
