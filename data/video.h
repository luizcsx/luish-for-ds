#ifndef LUISH_DATA_VIDEO_H
#define LUISH_DATA_VIDEO_H

#define COLOR_BACKGROUND  0x0000  // Pure Black
#define COLOR_TEXT        0x7FFF  // Bright White
#define COLOR_ACCENT      0x39E7  // Dark Gray for layout dividers

void video_init(void);

void video_clear_screens(void);

void video_draw_divider(void);

void video_print_text(const char* text, int x, int y);

#endif // LUISH_DATA_VIDEO_H
