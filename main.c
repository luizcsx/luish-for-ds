#define REG_DISPCNT      *(volatile unsigned int*)0x04000000
#define VRAM_A_CR        *(volatile unsigned int*)0x04000240
#define VRAM_A           ((volatile unsigned short*)0x06800000)

#define REG_DB_DISPCNT   *(volatile unsigned int*)0x04001000
#define VRAM_C_CR        *(volatile unsigned int*)0x04000242
#define VRAM_C           ((volatile unsigned short*)0x06200000)

#define COLOR_RED        0x001F
#define COLOR_YELLOW     0x03FF
#define COLOR_BLACK      0x0000

const unsigned char char_L[8] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00};

void draw_pixel_sub(int x, int y, unsigned short color) {
    VRAM_C[y * 256 + x] = color;
}

int main(void) {
    VRAM_A_CR = 0x80;
    REG_DISPCNT = 0x00020400;

    VRAM_C_CR = 0x82;
    REG_DB_DISPCNT = 0x00020400;

    for (int i = 0; i < 256 * 192; i++) {
        VRAM_A[i] = COLOR_RED;
    }

    for (int i = 0; i < 256 * 192; i++) {
        VRAM_C[i] = COLOR_YELLOW;
    }

    int startX = 124, startY = 92;
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if (char_L[l] & (0x80 >> c)) {
                draw_pixel_sub(startX + (c*2), startY + (l*2), COLOR_BLACK);
                draw_pixel_sub(startX + (c*2)+1, startY + (l*2), COLOR_BLACK);
                draw_pixel_sub(startX + (c*2), startY + (l*2)+1, COLOR_BLACK);
                draw_pixel_sub(startX + (c*2)+1, startY + (l*2)+1, COLOR_BLACK);
            }
        }
    }

    while (1) {
    }
    return 0;
}
