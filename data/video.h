#ifndef VIDEO_H
#define VIDEO_H

#define COLOR_BACKGROUND  0x0000
#define COLOR_TEXT        0xFFFF
#define COLOR_ACCENT      0x03E0

void video_init(void);
void video_clear_screens(void);
void video_draw_divider(void);
void video_print_text(const char* text, int x, int y);

#endif
