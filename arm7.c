#include <nds.h>

int main(void) {
    defaultExceptionHandler();
    while (1) {
        swiWaitForVBlank();
    }
    return 0;
}
