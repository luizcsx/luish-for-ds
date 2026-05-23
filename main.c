#include "video.h"

#define REG_KEYINPUT  *(volatile unsigned short*)0x04000130
#define REG_VCOUNT    *(volatile unsigned short*)0x04000006

#define KEY_UP     (1 << 6)
#define KEY_DOWN   (1 << 7)
#define KEY_A      (1 << 0)

#define VRAM_TOP   ((volatile unsigned short*)0x06800000)

void wait_vblank(void) {
    while (REG_VCOUNT >= 192);
    while (REG_VCOUNT < 192);
}

void clear_character_slot(int x, int y) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int pixel = (y + row) * 256 + (x + col);
            if (pixel >= 0 && pixel < 256 * 192) {
                VRAM_TOP[pixel] = COLOR_BACKGROUND;
            }
        }
    }
}

void draw_welcome_screen(void) {
    video_clear_screens();
    video_draw_divider();
    video_print_text("Initialize the system?", 32, 40);
    video_print_text("  Yes", 48, 64);
    video_print_text("  No", 48, 80);
    video_print_text(">", 48, 64); 
}

void draw_main_menu(void) {
    video_clear_screens();
    video_draw_divider();
    video_print_text("LUISH MENU", 32, 40);
    video_print_text("  1. Credits", 48, 64);
    video_print_text("  2. Back", 48, 80);
    video_print_text(">", 48, 64); 
}

int main(void) {
    video_init();
    wait_vblank();
    
    int current_screen = 0;
    int selected_option = 0;
    unsigned short last_keys = 0xFFFF;

    draw_welcome_screen();

    while (1) {
        wait_vblank();
        
        unsigned short current_keys = REG_KEYINPUT;
        unsigned short pressed_keys = (last_keys ^ current_keys) & (~current_keys);
        last_keys = current_keys;

        if (current_screen == 0) {
            if (pressed_keys & (KEY_DOWN | KEY_UP)) {
                if (selected_option == 0) {
                    clear_character_slot(48, 64);
                    selected_option = 1;
                    video_print_text(">", 48, 80);
                } else {
                    clear_character_slot(48, 80);
                    selected_option = 0;
                    video_print_text(">", 48, 64);
                }
            }
            
            if (pressed_keys & KEY_A) {
                if (selected_option == 0) {
                    current_screen = 1;
                    selected_option = 0; 
                    draw_main_menu();
                } else {
                    video_clear_screens();
                    video_draw_divider();
                    video_print_text("Boot aborted.", 32, 64);
                    while(1) { wait_vblank(); }
                }
            }
        }
        else if (current_screen == 1) {
            if (pressed_keys & (KEY_DOWN | KEY_UP)) {
                if (selected_option == 0) {
                    clear_character_slot(48, 64);
                    selected_option = 1;
                    video_print_text(">", 48, 80);
                } else {
                    clear_character_slot(48, 80);
                    selected_option = 0;
                    video_print_text(">", 48, 64);
                }
            }

            if (pressed_keys & KEY_A) {
                if (selected_option == 0) {
                    video_clear_screens();
                    video_draw_divider();
                    video_print_text("Made by Luiz Miguel.", 32, 64);
                    while(1) { wait_vblank(); }
                } 
                else if (selected_option == 1) {
                    current_screen = 0;
                    selected_option = 0; 
                    draw_welcome_screen();
                }
            }
        }
    }

    return 0;
}
