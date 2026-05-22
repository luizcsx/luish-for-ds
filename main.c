#include "data/video.h"

#define REG_VCOUNT *(volatile unsigned short*)0x04000006

void wait_vblank(void) {
    while (REG_VCOUNT >= 192);
    while (REG_VCOUNT < 192);
}

int main(void) {
    video_init();
    wait_vblank();
    
    video_clear_screens();
    video_draw_divider();

    video_print_text("Luish Kernel", 8, 6);
    video_print_text("Hello, made by Luiz Miguel", 8, 30);

    while (1) {
        wait_vblank();
    }

    return 0;
}
