/* ee-2.9-991111: func_00320800, libgcc2 find_exception_handler: scans the inner-to-outer region table for a handler covering pc. */
typedef void *(*__eh_matcher)(void *, void *, void *);

typedef struct {
    __eh_matcher match_function;
    short language;
    short version;
} __eh_info;

typedef struct exception_table {
    void *start_region;
    void *end_region;
    void *exception_handler;
    void *match_info;
} exception_table;

typedef struct exception_descriptor {
    void *runtime_space;
    void *lang_info;
    exception_table table[1];
} exception_descriptor;

__attribute__((section(".text.func_00320800")))
void *func_00320800(void *pc, exception_descriptor *table, __eh_info *eh_info,
                    int rethrow, int *cleanup)
{
    void *retval = 0;
    *cleanup = 1;
    if (table) {
        int pos = 0;
        exception_table *tab = &(table->table[0]);

        if (rethrow) {
            pos = ((exception_table *)pc) - tab;
            pc = ((exception_table *)pc)->end_region - 1;

            if (tab[pos].start_region != (void *)-1)
                pos++;
        } else
            pc--;

        for (; tab[pos].start_region != (void *)-1; pos++) {
            if (tab[pos].start_region <= pc && tab[pos].end_region > pc) {
                if (tab[pos].match_info) {
                    __eh_matcher matcher = eh_info->match_function;
                    if (matcher) {
                        void *ret = (*matcher)((void *)eh_info,
                                               tab[pos].match_info, table);
                        if (ret) {
                            if (retval == 0)
                                retval = tab[pos].exception_handler;
                            *cleanup = 0;
                            return retval;
                        }
                    }
                } else {
                    if (retval == 0)
                        retval = tab[pos].exception_handler;
                }
            }
        }
    }
    return retval;
}
