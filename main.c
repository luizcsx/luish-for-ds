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
    
    video_clear_screens();
    video_draw_divider();
    video_print_text("Initialize the system?", 32, 40);
    video_print_text("  Yes", 48, 64);
    video_print_text("  No", 48, 80);

    int selected_index = 0; 
    unsigned short last_keys = 0xFFFF;

    video_print_text(">", 48, 64);

    while (1) {
        wait_vblank();
        
        unsigned short current_keys = REG_KEYINPUT;
        unsigned short pressed = (last_keys ^ current_keys) & (~current_keys);
        last_keys = current_keys;

        if (pressed & (KEY_DOWN | KEY_UP)) {
            if (selected_index == 0) {
                video_print_text(" ", 48, 64);
                selected_index = 1;
                video_print_text(">", 48, 80);
            } else {
                video_print_text(" ", 48, 80);
                selected_index = 0;
                video_print_text(">", 48, 64);
            }
        }
        
        if (pressed & KEY_A) {
            video_clear_screens();
            video_draw_divider();
            if (selected_index == 0) {
                video_print_text("Booting Luish system...", 32, 64);
            } else {
                video_print_text("Boot aborted.", 32, 64);
            }
            while(1) { wait_vblank(); }
        }
    }

    return 0;
}
