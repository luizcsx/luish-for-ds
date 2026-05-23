#include "video.h"

#define REG_POWERCNT    *(volatile unsigned short*)0x04000304
#define REG_DISPCNT     *(volatile unsigned int*)0x04000000
#define REG_DB_DISPCNT  *(volatile unsigned int*)0x04001000

#define VRAM_A_CR       *(volatile unsigned char*)0x04000240
#define VRAM_C_CR       *(volatile unsigned char*)0x04000242

extern const unsigned char font_data[2048];

void video_init(void) {
    REG_POWERCNT = 0x820F;    

    VRAM_A_CR = 0x80;      

    VRAM_C_CR = 0x84;      
    
    REG_DISPCNT    = 0x00020000; 
    REG_DB_DISPCNT = 0x00020000; 
    
    fill_screen(VRAM_TOP,    COLOR_BG);
    fill_screen(VRAM_BOTTOM, COLOR_BG);
}

void wait_vblank(void) {
    volatile unsigned short* reg_vcount = (volatile unsigned short*)0x04000006;
    while (*reg_vcount >= 192);
    while (*reg_vcount < 192);
}

void fill_screen(volatile unsigned short* vram, unsigned short color) {
    for (int i = 0; i < SCREEN_PIXELS; i++) {
        vram[i] = color;
    }
}

void draw_pixel(volatile unsigned short* vram, int x, int y, unsigned short color) {
    if ((unsigned)x < SCREEN_W && (unsigned)y < SCREEN_H) {
        vram[y * SCREEN_W + x] = color;
    }
}

void draw_divider(void) {
    for (int x = 0; x < SCREEN_W; x++) {
        draw_pixel(VRAM_TOP,    x, SCREEN_H - 1, COLOR_BLACK);
        draw_pixel(VRAM_BOTTOM, x, 0,            COLOR_BLACK);
    }
}

void print_text(const char* text, int x, int y, volatile unsigned short* vram, unsigned short color) {
    int start_x = x;
    
    while (*text) {
        char c = *text++;
        
        if (c == '\n') {
            x = start_x;
            y += 8;
            continue;
        }
        
        if (c < 32 || c > 127) c = ' ';
        
        int glyph_offset = (c - 32) * 8;
        
        for (int row = 0; row < 8; row++) {
            unsigned char bits = font_data[glyph_offset + row];
            for (int col = 0; col < 8; col++) {
                if (bits & (0x80 >> col)) {
                    draw_pixel(vram, x + col, y + row, color);
                }
            }
        }
        x += 8;
    }
}
