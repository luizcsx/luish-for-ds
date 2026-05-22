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

void draw_menu(int selected_index) {
    video_clear_screens();
    video_draw_divider();

    video_print_text("Initialize the system?", 4, 4);

    if (selected_index == 0) {
        video_print_text("> Yes", 6, 8);
        video_print_text("  No", 6, 10);
    } else {
        video_print_text("  Yes", 6, 8);
        video_print_text("> No", 6, 10);
    }
}

int main(void) {
    video_init();
    wait_vblank();
    
    int selected_index = 0; 
    int total_options = 2;
    unsigned short last_keys = 0xFFFF;

    draw_menu(selected_index);

    while (1) {
        wait_vblank();
        
        unsigned short current_keys = REG_KEYINPUT;
        unsigned short pressed = (last_keys ^ current_keys) & (~current_keys);
        last_keys = current_keys;

        int changed = 0;

        if (pressed & KEY_DOWN) {
            selected_index = (selected_index + 1) % total_options;
            changed = 1;
        } 
        else if (pressed & KEY_UP) {
            selected_index = (selected_index - 1 + total_options) % total_options;
            changed = 1;
        }
        
        if (changed) {
            draw_menu(selected_index);
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
