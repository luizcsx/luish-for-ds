#include "video.h"

#define REG_KEYINPUT      *(volatile unsigned short*)0x04000130
#define REG_VCOUNT        *(volatile unsigned short*)0x04000006

#define REG_SOUNDCNT      *(volatile unsigned short*)0x04000500
#define REG_SOUNDBIAS     *(volatile unsigned short*)0x04000504

#define REG_CH0_CNT       *(volatile unsigned int*)0x04000400
#define REG_CH0_SAD       *(volatile unsigned int*)0x04000404
#define REG_CH0_TMR       *(volatile unsigned short*)0x04000408
#define REG_CH0_LEN       *(volatile unsigned int*)0x0400040C

#define KEY_UP     (1 << 6)
#define KEY_DOWN   (1 << 7)
#define KEY_A      (1 << 0)

#define VRAM_BOTTOM   ((volatile unsigned short*)0x06200000)

void wait_vblank(void) {
    while (REG_VCOUNT >= 192);
    while (REG_VCOUNT < 192);
}

void init_native_audio(void) {
    REG_SOUNDCNT = 0x807F;
    REG_SOUNDBIAS = 0x0200;
}

void trigger_audio_loop(void) {
    REG_CH0_SAD = 0x023F0000; 
    REG_CH0_TMR = (unsigned short)(-16777216 / 22050);
    REG_CH0_LEN = 0x7FFF;
    REG_CH0_CNT = 0xC47F0000;
}

void clear_bottom_character_slot(int x, int y) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int pixel = (y + row) * 256 + (x + col);
            if (pixel >= 0 && pixel < 256 * 192) {
                VRAM_BOTTOM[pixel] = COLOR_BACKGROUND;
            }
        }
    }
}

void draw_welcome_screen(void) {
    video_clear_screens();
    video_draw_divider();
    video_print_text_ext("Initialize the system?", 32, 40, 1);
    video_print_text_ext("  Yes", 48, 64, 1);
    video_print_text_ext("  No", 48, 80, 1);
    video_print_text_ext(">", 48, 64, 1); 
}

void draw_main_menu(void) {
    video_clear_screens();
    video_draw_divider();
    video_print_text_ext("Luish", 32, 40, 1);
    video_print_text_ext("  1. Credits", 48, 64, 1);
    video_print_text_ext("  2. Back", 48, 80, 1);
    video_print_text_ext(">", 48, 64, 1); 
}

int main(void) {
    video_init();
    init_native_audio();
    trigger_audio_loop();
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
                    clear_bottom_character_slot(48, 64);
                    selected_option = 1;
                    video_print_text_ext(">", 48, 80, 1);
                } else {
                    clear_bottom_character_slot(48, 80);
                    selected_option = 0;
                    video_print_text_ext(">", 48, 64, 1);
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
                    video_print_text_ext("Boot aborted.", 32, 64, 1);
                    while(1) { wait_vblank(); }
                }
            }
        }
        else if (current_screen == 1) {
            if (pressed_keys & (KEY_DOWN | KEY_UP)) {
                if (selected_option == 0) {
                    clear_bottom_character_slot(48, 64);
                    selected_option = 1;
                    video_print_text_ext(">", 48, 80, 1);
                } else {
                    clear_bottom_character_slot(48, 80);
                    selected_option = 0;
                    video_print_text_ext(">", 48, 64, 1);
                }
            }

            if (pressed_keys & KEY_A) {
                if (selected_option == 0) {
                    video_clear_screens();
                    video_draw_divider();
                    video_print_text_ext("Made by Luiz Miguel.", 32, 64, 1);
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
