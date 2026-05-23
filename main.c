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

void apagar_caractere(int x, int y) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int pixel = (y + row) * 256 + (x + col);
            if (pixel >= 0 && pixel < 256 * 192) {
                VRAM_TOP[pixel] = COLOR_BACKGROUND;
            }
        }
    }
}

void desenhar_tela_inicial(void) {
    video_clear_screens();
    video_draw_divider();
    video_print_text("Initialize the system?", 32, 40);
    video_print_text("  Yes", 48, 64);
    video_print_text("  No", 48, 80);
    video_print_text(">", 48, 64);
}

void desenhar_menu_principal(void) {
    video_clear_screens();
    video_draw_divider();
    video_print_text("Luish", 32, 40);
    video_print_text("  1. Creditos", 48, 64);
    video_print_text("  2. Voltar", 48, 80);
    video_print_text(">", 48, 64);
}


int main(void) {
    video_init();
    wait_vblank();
    
    int tela_atual = 0;
    int selected_index = 0;
    unsigned short last_keys = 0xFFFF;

    desenhar_tela_inicial();

    while (1) {
        wait_vblank();
        
        unsigned short current_keys = REG_KEYINPUT;
        unsigned short pressed = (last_keys ^ current_keys) & (~current_keys);
        last_keys = current_keys;

        if (tela_atual == 0) {
            if (pressed & (KEY_DOWN | KEY_UP)) {
                if (selected_index == 0) {
                    apagar_caractere(48, 64);
                    selected_index = 1;
                    video_print_text(">", 48, 80);
                } else {
                    apagar_caractere(48, 80);
                    selected_index = 0;
                    video_print_text(">", 48, 64);
                }
            }
            
            if (pressed & KEY_A) {
                if (selected_index == 0) {
                    tela_atual = 1;
                    selected_index = 0;
                    desenhar_menu_principal();
                } else {
                    video_clear_screens();
                    video_draw_divider();
                    video_print_text("Boot aborted.", 32, 64);
                    while(1) { wait_vblank(); }
                }
            }
        }
            
        else if (tela_atual == 1) {
            if (pressed & (KEY_DOWN | KEY_UP)) {
                if (selected_index == 0) {
                    apagar_caractere(48, 64);
                    selected_index = 1;
                    video_print_text(">", 48, 80);
                } else {
                    apagar_caractere(48, 80);
                    selected_index = 0;
                    video_print_text(">", 48, 64);
                }
            }

            if (pressed & KEY_A) {
                if (selected_index == 0) {
                    video_clear_screens();
                    video_draw_divider();
                    video_print_text("Made by Luiz Miguel.", 32, 64);
                    while(1) { wait_vblank(); }
                } 
                else if (selected_index == 1) {
                    tela_atual = 0;
                    selected_index = 0;
                    desenhar_tela_inicial();
                }
            }
        }
    }

    return 0;
}
