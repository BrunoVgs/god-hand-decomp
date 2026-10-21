/* cygnus-2.96 matched TU. */
#include "godhand/CriServer.h"
typedef struct CriServerCallback {
    char reserved[0x10];
    void * volatile callback;
    void * volatile context;
} CriServerCallback;
extern char D_00460B20[];
extern void func_003B9DE0(char *message);
/* Set the server callback and its context after validating all pointers. */
__attribute__((section(".text.func_003BA8C0")))
void func_003BA8C0(CriServerCallback *server, void *callback, void *context) {
    if (server == 0 || callback == 0 || context == 0) {
        func_003B9DE0(D_00460B20);
        return;
    }
    server->context = context;
    server->callback = callback;
}
