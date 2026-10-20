/* cygnus-2.96: func_003475F0, searches the stored chunk at +0x194 for the tag and hands the result to
 * func_0035FC88. */
typedef signed char Sint8;
typedef int Sint32;
typedef struct { Sint8 *data; Sint32 len; } SJCK;
typedef struct { Sint8 *data; Sint32 len; } SJTAG;
typedef struct { int set; SJCK ck; } TagRec;
typedef struct {
    char pad0[0xA8];
    void *taghn; /* 0xA8 */
    char padAC[0x194 - 0xAC];
    TagRec rec; /* 0x194 */
} SfxWork;
extern Sint8 D_00458CE0[];
extern Sint8 D_00458CE8[];
extern Sint8 *SJ_SearchTag(SJCK *ck, Sint8 *tag, Sint8 *endtag, SJTAG *tagck);
extern void func_0035FC88(void *hn, Sint8 *data, Sint32 len);

__attribute__((section(".text.func_003475F0")))
void func_003475F0(SfxWork *w)
{
    TagRec *rec = &w->rec;
    SJCK ck;
    SJTAG tag;
    void *hn;

    hn = w->taghn;
    if (rec->ck.data == 0) {
        func_0035FC88(hn, 0, 0);
        return;
    }
    ck.data = rec->ck.data;
    ck.len = rec->ck.len;
    if (SJ_SearchTag(&ck, D_00458CE0, D_00458CE8, &tag) == 0)
        func_0035FC88(hn, 0, 0);
    else
        func_0035FC88(hn, tag.data, tag.len);
}
