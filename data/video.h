#ifndef VIDEO_H
#define VIDEO_H

#include <nds.h>

#define VRAM_TOP    ((volatile unsigned short*)0x06800000)
#define VRAM_BOTTOM ((volatile unsigned short*)0x06200000)

#define SCREEN_W      256
#define SCREEN_H      192
#define SCREEN_PIXELS (SCREEN_W * SCREEN_H)

#define COLOR_BG     RGB15(4, 8, 4)
#define COLOR_TEXT   RGB15(31,31,31)
#define COLOR_SELECT RGB15(0, 31, 0)
#define COLOR_BLACK  RGB15(0, 0, 0)

void video_init(void);
void wait_vblank(void);
void draw_pixel(volatile unsigned short* vram, int x, int y, unsigned short color);
void fill_screen(volatile unsigned short* vram, unsigned short color);
void draw_hline(volatile unsigned short* vram, int y, unsigned short color);
void draw_rect_outline(volatile unsigned short* vram, int x0, int y0, int x1, int y1, unsigned short color);
void fill_rect(volatile unsigned short* vram, int x0, int y0, int x1, int y1, unsigned short color);
void print_text(const char* text, int x, int y, volatile unsigned short* vram, unsigned short color);

#endif
