#define REG_POWERCNT    *(volatile unsigned int*)0x04000304
#define REG_DISPCNT     *(volatile unsigned int*)0x04000000
#define VRAM_A_CR       *(volatile unsigned int*)0x04000240

#define REG_DB_DISPCNT  *(volatile unsigned int*)0x04001000
#define VRAM_C_CR       *(volatile unsigned int*)0x04000242

#define REG_VCOUNT      *(volatile unsigned short*)0x04000006

#define VRAM_TOP        ((volatile unsigned short*)0x06800000) // VRAM A (Main)
#define VRAM_BOTTOM     ((volatile unsigned short*)0x06200000) // VRAM C (Sub)

#define COLOR_BACKGROUND  0x0000  // Preto Absoluto
#define COLOR_TEXT        0x7FFF  // Branco Brilhante
#define COLOR_ACCENT      0x39E7  // Cinza Escuro para divisores e bordas

typedef struct {
    int cursor_x;
    int cursor_y;
} Terminal;

Terminal sys_terminal = {8, 8};

typedef struct {
    unsigned short touch_x;
    unsigned short touch_y;
    unsigned char is_pressed;
} StylusInput;

volatile StylusInput sys_touch = {0, 0, 0};

const unsigned char fonte[128][8] = {
    ['H'] = {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},
    ['e'] = {0x3C, 0x66, 0x7E, 0x60, 0x62, 0x3C, 0x00, 0x00},
    ['l'] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x1C, 0x00, 0x00},
    ['o'] = {0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00, 0x00},
    ['m'] = {0x66, 0xEF, 0xD6, 0xD6, 0xC6, 0xC6, 0x00, 0x00},
    ['a'] = {0x3C, 0x06, 0x3E, 0x66, 0x66, 0x3D, 0x00, 0x00},
    ['d'] = {0x06, 0x06, 0x3E, 0x66, 0x66, 0x3D, 0x00, 0x00},
    ['b'] = {0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00, 0x00},
    ['y'] = {0x66, 0x66, 0x66, 0x3E, 0x06, 0x3C, 0x00, 0x00},
    ['L'] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00, 0x00},
    ['u'] = {0x66, 0x66, 0x66, 0x66, 0x66, 0x3D, 0x00, 0x00},
    ['i'] = {0x18, 0x00, 0x18, 0x18, 0x18, 0x1C, 0x00, 0x00},
    ['z'] = {0x7E, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00, 0x00},
    ['M'] = {0x63, 0x77, 0x7B, 0x6B, 0x63, 0x63, 0x00, 0x00},
    ['g'] = {0x3D, 0x66, 0x66, 0x3E, 0x06, 0x3C, 0x00, 0x00},
    [','] = {0x00, 0x00, 0x00, 0x18, 0x18, 0x10, 0x20, 0x00},
    [' '] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

void esperar_vblank() {
    while (REG_VCOUNT >= 192);
    while (REG_VCOUNT < 192);
}

void terminal_escrever_char(char c) {
    if (c == '\n') {
        sys_terminal.cursor_x = 8;
        sys_terminal.cursor_y += 10;
        return;
    }

    if (sys_terminal.cursor_x + 8 > 248) {
        sys_terminal.cursor_x = 8;
        sys_terminal.cursor_y += 10;
    }

    if (sys_terminal.cursor_y + 8 > 180) {
        sys_terminal.cursor_y = 30;
        for (int i = 30 * 256; i < 256 * 192; i++) VRAM_TOP[i] = COLOR_BACKGROUND;
    }

    for (int linha = 0; linha < 8; linha++) {
        unsigned char dados_linha = fonte[(int)c][linha];
        for (int coluna = 0; coluna < 8; coluna++) {
            if (dados_linha & (0x80 >> coluna)) {
                int pixel = (sys_terminal.cursor_y + linha) * 256 + (sys_terminal.cursor_x + coluna);
                if (pixel >= 0 && pixel < 256 * 192) {
                    VRAM_TOP[pixel] = COLOR_TEXT;
                }
            }
        }
    }
    sys_terminal.cursor_x += 8;
}

void terminal_escrever_texto(const char* texto) {
    while (*texto) {
        terminal_escrever_char(*texto);
        texto++;
    }
}

void atualizar_sistema_toque() {
    if (sys_touch.is_pressed) {
    }
}

int main(void) {
    REG_POWERCNT = 0x80000000; 
    
    VRAM_A_CR = 0x80;
    REG_DISPCNT = 0x00020400;
    
    VRAM_C_CR = 0x82;
    REG_DB_DISPCNT = 0x00020400; 

    esperar_vblank();

    for (int i = 0; i < 256 * 192; i++) {
        VRAM_TOP[i] = COLOR_BACKGROUND;
        VRAM_BOTTOM[i] = COLOR_BACKGROUND;
    }

    for (int x = 0; x < 256; x++) {
        VRAM_TOP[20 * 256 + x] = COLOR_ACCENT;
    }

    sys_terminal.cursor_x = 8;
    sys_terminal.cursor_y = 6;
    terminal_escrever_texto("Luish Kernel");

    sys_terminal.cursor_x = 8;
    sys_terminal.cursor_y = 30;
    terminal_escrever_texto("Hello, made by Luiz Miguel");

    while (1) {
        atualizar_sistema_toque();
        esperar_vblank();
    }

    return 0;
}
