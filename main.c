#include "video.h"

#define REG_KEYINPUT  *(volatile unsigned short*)0x04000130
#define REG_VCOUNT    *(volatile unsigned short*)0x04000006

#define KEY_UP     (1 << 6)
#define KEY_DOWN   (1 << 7)
#define KEY_A      (1 << 0)

void wait_vblank(void) {
    while (REG_VCOUNT >= 192);
    while (REG_VCOUNT < 192);
}

int main(void) {
    video_init();
    wait_vblank();
    
    int selected_index = 0; 
    unsigned short last_keys = 0xFFFF;

    while (1) {
        wait_vblank();
        
        video_print_text("Initialize the system?", 4, 4);
        video_draw_divider();

        if (selected_index == 0) {
            video_print_text("> Yes", 6, 8);
            video_print_text("  No ", 6, 10);
        } else {
            video_print_text("  Yes", 6, 8);
            video_print_text("> No ", 6, 10);
        }

        unsigned short current_keys = REG_KEYINPUT;
        unsigned short pressed = (last_keys ^ current_keys) & (~current_keys);
        last_keys = current_keys;

        if (pressed & (KEY_DOWN | KEY_UP)) {
            if (selected_index == 0) {
                selected_index = 1;
            } else {
                selected_index = 0;
            }
        }
        
        if (pressed & KEY_A) {
            video_clear_screens();
            video_draw_divider();
            if (selected_index == 0) {
                video_print_text("Booting Luish system...", 4, 8);
            } else {
                video_print_text("Boot Aborted.", 4, 8);
            }
            while(1) { wait_vblank(); }
        }
    }

    return 0;
}
