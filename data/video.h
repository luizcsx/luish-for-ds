#ifndef VIDEO_H
#define VIDEO_H

#define REG_POWERCNT    *(volatile unsigned short*)0x04000304
#define REG_VCOUNT      *(volatile unsigned short*)0x04000006

#define REG_DISPCNT     *(volatile unsigned int*)0x04000000
#define REG_DB_DISPCNT  *(volatile unsigned int*)0x04001000

#define VRAM_A_CR       *(volatile unsigned char*)0x04000240
#define VRAM_C_CR       *(volatile unsigned char*)0x04000242

#define VRAM_TOP        ((volatile unsigned short*)0x06800000)
#define VRAM_BOTTOM     ((volatile unsigned short*)0x06200000)

#define SCREEN_W        256
#define SCREEN_H        192
#define SCREEN_PIXELS   (SCREEN_W * SCREEN_H)

#define COLOR_BG        0x4200u
#define COLOR_TEXT      0x7FFFu
#define COLOR_SELECT    0x7FE0u
#define COLOR_BLACK     0x0000u

void video_init(void);
void wait_vblank(void);
void draw_pixel(volatile unsigned short* vram, int x, int y, unsigned short color);
void fill_screen(volatile unsigned short* vram, unsigned short color);
void print_text(const char* text, int x, int y, volatile unsigned short* vram, unsigned short color);
void draw_hline(volatile unsigned short* vram, int y, unsigned short color);
void draw_rect_outline(volatile unsigned short* vram, int x0, int y0, int x1, int y1, unsigned short color);
void fill_rect(volatile unsigned short* vram, int x0, int y0, int x1, int y1, unsigned short color);

#endif /* VIDEO_H */
