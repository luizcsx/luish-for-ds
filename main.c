#define REG_POWERCNT    *(volatile unsigned int*)0x04000304
#define REG_DISPCNT     *(volatile unsigned int*)0x04000000
#define VRAM_A_CR       *(volatile unsigned int*)0x04000240
#define REG_DB_DISPCNT  *(volatile unsigned int*)0x04001000
#define VRAM_D_CR       *(volatile unsigned int*)0x04000243

#define REG_KEYINPUT    *(volatile unsigned short*)0x04000130
#define REG_VCOUNT      *(volatile unsigned short*)0x04000006

#define REG_SOUNDCNT    *(volatile unsigned short*)0x04000500
#define REG_SOUNDBIAS   *(volatile unsigned short*)0x04000504
#define REG_CH0_CNT     *(volatile unsigned int*)0x04000400
#define REG_CH0_TMR     *(volatile unsigned short*)0x04000408

#define VRAM_TOP        ((volatile unsigned short*)0x06800000) // Bank A (Top Screen)
#define VRAM_BOTTOM     ((volatile unsigned short*)0x06600000) // Bank D (Bottom Screen)

#define COLOR_BG        0x4200 // Deep Factory Navy Blue
#define COLOR_TEXT      0x7FFF // Crisp White
#define COLOR_SELECT    0x03E0 // Selection Highlight Yellow
#define COLOR_BLACK     0x0000 // Solid Black

#define KEY_UP          (1 << 6)
#define KEY_DOWN        (1 << 7)
#define KEY_LEFT        (1 << 5)
#define KEY_RIGHT       (1 << 4)
#define KEY_A           (1 << 0)

const unsigned char basic_font[128][8] = {
    [' '] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    ['!'] = {0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
    ['?'] = {0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00},
    ['.'] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},
    [':'] = {0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00},
    ['/'] = {0x00, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00, 0x00},
    ['_'] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00},
    ['-'] = {0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00},
    ['*'] = {0x00, 0x24, 0x18, 0x7E, 0x18, 0x24, 0x00, 0x00}, 
    ['%'] = {0x62, 0x66, 0x0C, 0x18, 0x30, 0x66, 0x46, 0x00}, 
    ['['] = {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},
    [']'] = {0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00},
    ['0'] = {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x3C, 0x00, 0x00},
    ['1'] = {0x18, 0x38, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00},
    ['2'] = {0x3C, 0x66, 0x0C, 0x18, 0x30, 0x7E, 0x00, 0x00},
    ['3'] = {0x3C, 0x66, 0x1C, 0x06, 0x66, 0x3C, 0x00, 0x00},
    ['4'] = {0x1C, 0x3C, 0x5C, 0x7E, 0x1C, 0x1C, 0x00, 0x00},
    ['5'] = {0x7E, 0x60, 0x7C, 0x06, 0x66, 0x3C, 0x00, 0x00},
    ['6'] = {0x3C, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00, 0x00},
    ['7'] = {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x00, 0x00},
    ['8'] = {0x3C, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00, 0x00},
    ['9'] = {0x3C, 0x66, 0x3E, 0x06, 0x0C, 0x38, 0x00, 0x00},
    ['A'] = {0x3C, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},
    ['B'] = {0x7C, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00, 0x00},
    ['C'] = {0x3C, 0x66, 0x60, 0x60, 0x66, 0x3C, 0x00, 0x00},
    ['D'] = {0x78, 0x6C, 0x66, 0x66, 0x6C, 0x78, 0x00, 0x00},
    ['E'] = {0x7E, 0x60, 0x78, 0x60, 0x60, 0x7E, 0x00, 0x00},
    ['F'] = {0x7E, 0x60, 0x78, 0x60, 0x60, 0x60, 0x00, 0x00},
    ['G'] = {0x3E, 0x60, 0x60, 0x6E, 0x66, 0x3E, 0x00, 0x00},
    ['H'] = {0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},
    ['I'] = {0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00},
    ['J'] = {0x0F, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3C, 0x00},
    ['K'] = {0x66, 0x6C, 0x78, 0x78, 0x6C, 0x66, 0x00, 0x00},
    ['L'] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00, 0x00},
    ['M'] = {0x63, 0x77, 0x7B, 0x6B, 0x63, 0x63, 0x00, 0x00},
    ['N'] = {0x63, 0x73, 0x7B, 0x6F, 0x67, 0x63, 0x00, 0x00},
    ['O'] = {0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00, 0x00},
    ['P'] = {0x7C, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00, 0x00},
    ['Q'] = {0x3C, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x0E, 0x00},
    ['R'] = {0x7C, 0x66, 0x7C, 0x6C, 0x66, 0x66, 0x00, 0x00},
    ['S'] = {0x3E, 0x60, 0x3C, 0x06, 0x06, 0x7C, 0x00, 0x00},
    ['T'] = {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00},
    ['U'] = {0x66, 0x66, 0x66, 0x66, 0x66, 0x3D, 0x00, 0x00},
    ['V'] = {0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00},
    ['W'] = {0xC6, 0xC6, 0xD6, 0xFE, 0xEE, 0x66, 0x00, 0x00},
    ['X'] = {0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00, 0x00},
    ['Y'] = {0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00, 0x00},
    ['Z'] = {0x7E, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00, 0x00},
    ['a'] = {0x00, 0x3E, 0x06, 0x3E, 0x66, 0x3B, 0x00, 0x00},
    ['b'] = {0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00, 0x00},
    ['c'] = {0x00, 0x3C, 0x66, 0x60, 0x66, 0x3C, 0x00, 0x00},
    ['d'] = {0x06, 0x06, 0x3E, 0x66, 0x66, 0x3D, 0x00, 0x00},
    ['e'] = {0x00, 0x3C, 0x66, 0x7E, 0x60, 0x3C, 0x00, 0x00},
    ['f'] = {0x1C, 0x22, 0x78, 0x20, 0x20, 0x70, 0x00, 0x00},
    ['g'] = {0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x7C, 0x00},
    ['h'] = {0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x00, 0x00},
    ['i'] = {0x18, 0x00, 0x18, 0x18, 0x18, 0x1C, 0x00, 0x00},
    ['j'] = {0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x4C, 0x38, 0x00},
    ['k'] = {0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0x00, 0x00},
    ['l'] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x1C, 0x00, 0x00},
    ['m'] = {0x00, 0x66, 0xEF, 0xD6, 0xD6, 0xC6, 0x00, 0x00},
    ['n'] = {0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00},
    ['o'] = {0x00, 0x3C, 0x66, 0x66, 0x66, 0x3C, 0x00, 0x00},
    ['p'] = {0x00, 0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x00},
    ['q'] = {0x00, 0x3D, 0x66, 0x66, 0x3D, 0x04, 0x04, 0x00},
    ['r'] = {0x00, 0xAE, 0x76, 0x60, 0x60, 0x60, 0x00, 0x00},
    ['s'] = {0x00, 0x3E, 0x60, 0x3C, 0x06, 0x7C, 0x00, 0x00},
    ['t'] = {0x30, 0x7C, 0x30, 0x30, 0x34, 0x18, 0x00, 0x00},
    ['u'] = {0x00, 0x66, 0x66, 0x66, 0x66, 0x3D, 0x00, 0x00},
    ['v'] = {0x00, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00, 0x00},
    ['w'] = {0x00, 0x82, 0x92, 0x92, 0xBA, 0x44, 0x00, 0x00},
    ['x'] = {0x00, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x00, 0x00},
    ['y'] = {0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x3C, 0x00},
    ['z'] = {0x00, 0x7E, 0x0C, 0x18, 0x30, 0x7E, 0x00, 0x00}
};

void system_video_init(void) {
    REG_POWERCNT = 0x80000000; 
    
    VRAM_A_CR = 0x80;
    REG_DISPCNT = 0x00020400;
    
    VRAM_D_CR = 0x80;
    REG_DB_DISPCNT = 0x00020400;
    
    for (int i = 0; i < 256 * 192; i++) {
        VRAM_TOP[i] = COLOR_BG;
        VRAM_BOTTOM[i] = COLOR_BG;
    }
}

void system_print_text(const char* text, int x, int y, int target_screen, unsigned short color) {
    volatile unsigned short* vram = (target_screen == 0) ? VRAM_TOP : VRAM_BOTTOM;
    int current_x = x;
    while (*text) {
        char c = *text;
        for (int row = 0; row < 8; row++) {
            unsigned char row_data = basic_font[(int)c][row];
            for (int col = 0; col < 8; col++) {
                if (row_data & (0x80 >> col)) {
                    int pixel = (y + row) * 256 + (current_x + col);
                    if (pixel >= 0 && pixel < 256 * 192) {
                        vram[pixel] = color;
                    }
                }
            }
        }
        current_x += 8;
        text++;
    }
}

void draw_horizontal_divider(void) {
    for (int x = 0; x < 256; x++) {
        VRAM_TOP[24 * 256 + x] = COLOR_TEXT;
        VRAM_BOTTOM[24 * 256 + x] = COLOR_TEXT;
    }
}

void draw_progress_bar_frame(void) {
    for (int x = 48; x < 208; x++) {
        VRAM_TOP[100 * 256 + x] = COLOR_TEXT;
        VRAM_TOP[112 * 256 + x] = COLOR_TEXT;
    }
    for (int y = 100; y <= 112; y++) {
        VRAM_TOP[y * 256 + 48] = COLOR_TEXT;
        VRAM_TOP[y * 256 + 208] = COLOR_TEXT;
    }
}

void update_progress_bar_fill(int current_width) {
    for (int y = 102; y < 111; y++) {
        for (int x = 50; x < 50 + current_width; x++) {
            VRAM_TOP[y * 256 + x] = COLOR_SELECT; 
        }
    }
}

void wait_vblank(void) {
    while (REG_VCOUNT >= 192);
    while (REG_VCOUNT < 192);
}

void init_hardware_audio(void) {
    REG_SOUNDCNT = 0x807F;     
    REG_SOUNDBIAS = 0x0200;    
}

void trigger_beep_sound(int frequency) {
    unsigned short timer_val = 51160;
    if (frequency == 600)  timer_val = 55212;
    if (frequency == 880)  timer_val = 59180;
    if (frequency == 1200) timer_val = 61212;
    if (frequency == 220)  timer_val = 35160;

    REG_CH0_TMR = timer_val; 
    REG_CH0_CNT = 0x877F0000;  
    for(int i = 0; i < 10; i++) wait_vblank(); 
    REG_CH0_CNT = 0x00000000;  
}

const char grid_characters[12][4] = {
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9",
    "-", "0", "OK"
};

const int grid_positions_x[12] = {
    64, 120, 176,
    64, 120, 176,
    64, 120, 176,
    64, 120, 176
};

const int grid_positions_y[12] = {
    60,  60,  60,
    90,  90,  90,
    120, 120, 120,
    150, 150, 150
};

void draw_security_pin_grid(int active_index) {
    for (int i = 0; i < 12; i++) {
        unsigned short current_color = (i == active_index) ? COLOR_SELECT : COLOR_TEXT;
        system_print_text("[   ]", grid_positions_x[i] - 8, grid_positions_y[i], 1, current_color);
        system_print_text(grid_characters[i], grid_positions_x[i], grid_positions_y[i], 1, current_color);
    }
}

int main(void) {
    system_video_init();
    init_hardware_audio();
    wait_vblank();
    
    system_print_text("Luish Factory Setup", 8, 8, 0, COLOR_TEXT);
    draw_horizontal_divider();
    system_print_text("Loading Luish files...", 48, 70, 0, COLOR_TEXT);
    draw_progress_bar_frame();
    
    char progress_string[5] = "0%";
    for (int progress = 0; progress <= 100; progress++) {
        wait_vblank();
        if ((progress & 1) == 0) {
            int current_width = (progress * 101) >> 6; 
            update_progress_bar_fill(current_width);
            
            if (progress < 10) {
                progress_string[0] = '0' + progress;
                progress_string[1] = '%';
                progress_string[2] = '\0';
            } else if (progress < 100) {
                int tens = 0;
                int units = progress;
                while (units >= 10) {
                    units -= 10;
                    tens++;
                }
                progress_string[0] = '0' + tens;
                progress_string[1] = '0' + units;
                progress_string[2] = '%';
                progress_string[3] = '\0';
            } else {
                progress_string[0] = '1';
                progress_string[1] = '0';
                progress_string[2] = '0';
                progress_string[3] = '%';
                progress_string[4] = '\0';
            }
            system_print_text(progress_string, 112, 130, 0, COLOR_SELECT);
        }
    }
    
    trigger_beep_sound(880); 
    
    system_video_init();
    draw_horizontal_divider();
    system_print_text("Security Authorization", 8, 8, 0, COLOR_TEXT);
    system_print_text("Enter System PIN code:", 48, 60, 0, COLOR_TEXT);
    system_print_text("[ _ ] [ _ ] [ _ ] [ _ ]", 48, 90, 0, COLOR_TEXT);
    
    int active_grid_slot = 0;
    int entered_digits_count = 0;
    int input_pin_buffer[4] = {-1, -1, -1, -1};
    const int actual_system_pin[4] = {1, 2, 3, 4}; 
    
    unsigned short previous_keys_state = 0xFFFF;
    draw_security_pin_grid(active_grid_slot);
    
    int system_authenticated = 0;
    while (!system_authenticated) {
        wait_vblank();
        unsigned short current_keys_state = REG_KEYINPUT;
        unsigned short registered_presses = (previous_keys_state ^ current_keys_state) & (~current_keys_state);
        previous_keys_state = current_keys_state;
        
        if (registered_presses & KEY_RIGHT) {
            int current_col = active_grid_slot;
            while (current_col >= 3) current_col -= 3;
            if (current_col < 2) active_grid_slot++;
            draw_security_pin_grid(active_grid_slot);
        }
        if (registered_presses & KEY_LEFT) {
            int current_col = active_grid_slot;
            while (current_col >= 3) current_col -= 3;
            if (current_col > 0) active_grid_slot--;
            draw_security_pin_grid(active_grid_slot);
        }
        if (registered_presses & KEY_DOWN) {
            if (active_grid_slot < 9) active_grid_slot += 3;
            draw_security_pin_grid(active_grid_slot);
        }
        if (registered_presses & KEY_UP) {
            if (active_grid_slot >= 3) active_grid_slot -= 3;
            draw_security_pin_grid(active_grid_slot);
        }
        
        if (registered_presses & KEY_A) {
            if (active_grid_slot == 11) {
                if (entered_digits_count == 4 && 
                    input_pin_buffer[0] == actual_system_pin[0] &&
                    input_pin_buffer[1] == actual_system_pin[1] &&
                    input_pin_buffer[2] == actual_system_pin[2] &&
                    input_pin_buffer[3] == actual_system_pin[3]) {
                    
                    system_authenticated = 1; 
                } else {
                    trigger_beep_sound(220); 
                    entered_digits_count = 0;
                    system_print_text("[ _ ] [ _ ] [ _ ] [ _ ]", 48, 90, 0, COLOR_TEXT);
                }
            } 
            else if (active_grid_slot == 9) {
                entered_digits_count = 0;
                system_print_text("[ _ ] [ _ ] [ _ ] [ _ ]", 48, 90, 0, COLOR_TEXT);
            }
            else {
                int typed_value = (active_grid_slot == 10) ? 0 : (active_grid_slot + 1);
                if (entered_digits_count < 4) {
                    trigger_beep_sound(600);
                    input_pin_buffer[entered_digits_count] = typed_value;
                    system_print_text("*", 56 + (entered_digits_count * 40), 90, 0, COLOR_SELECT);
                    entered_digits_count++;
                }
            }
        }
    }
    
    trigger_beep_sound(1200); 
    system_video_init();
    draw_horizontal_divider();
    
    system_print_text("Luish OS v1.0", 8, 8, 0, COLOR_TEXT);
    system_print_text("22/05/2026 - 23:33", 104, 8, 0, COLOR_SELECT); 
    
    system_print_text("System Active.", 48, 60, 0, COLOR_TEXT);
    
    system_print_text("1. Hardware Specifications", 24, 60, 1, COLOR_SELECT);
    system_print_text("2. Reset Firmware Settings", 24, 90, 1, COLOR_TEXT);
    system_print_text("3. Exit Console Shell", 24, 120, 1, COLOR_TEXT);
    
    int active_menu_index = 0;
    while (1) {
        wait_vblank();
        unsigned short current_keys_state = REG_KEYINPUT;
        unsigned short registered_presses = (previous_keys_state ^ current_keys_state) & (~current_keys_state);
        previous_keys_state = current_keys_state;
        
        if (registered_presses & KEY_DOWN) {
            active_menu_index++;
            if (active_menu_index > 2) active_menu_index = 0;
            
            system_print_text("1. Hardware Specifications", 24, 60, 1, (active_menu_index == 0) ? COLOR_SELECT : COLOR_TEXT);
            system_print_text("2. Reset Firmware Settings", 24, 90, 1, (active_menu_index == 1) ? COLOR_SELECT : COLOR_TEXT);
            system_print_text("3. Exit Console Shell", 24, 120, 1, (active_menu_index == 2) ? COLOR_SELECT : COLOR_TEXT);
            trigger_beep_sound(500);
        }
        if (registered_presses & KEY_UP) {
            active_menu_index--;
            if (active_menu_index < 0) active_menu_index = 2;
            
            system_print_text("1. Hardware Specifications", 24, 60, 1, (active_menu_index == 0) ? COLOR_SELECT : COLOR_TEXT);
            system_print_text("2. Reset Firmware Settings", 24, 90, 1, (active_menu_index == 1) ? COLOR_SELECT : COLOR_TEXT);
            system_print_text("3. Exit Console Shell", 24, 120, 1, (active_menu_index == 2) ? COLOR_SELECT : COLOR_TEXT);
            trigger_beep_sound(500);
        }
        
        if (registered_presses & KEY_A) {
            if (active_menu_index == 0) { 
                system_video_init();
                draw_horizontal_divider();
                system_print_text("Hardware Diagnostics", 8, 8, 0, COLOR_TEXT);
                
                system_print_text("CPU: ARM946E-S & ARM7TDMI", 16, 50, 1, COLOR_TEXT);
                system_print_text("BUS ENGINE: INTERNAL PSG", 16, 70, 1, COLOR_TEXT);
                system_print_text("VRAM BLOCK MAP: DIRECT LCD", 16, 90, 1, COLOR_TEXT);
                system_print_text("STATUS: OPERATIONAL", 16, 110, 1, COLOR_SELECT);
                while(1) { wait_vblank(); }
            }
            else {
                system_video_init();
                draw_horizontal_divider();
                system_print_text("Operation halted.", 48, 80, 0, COLOR_TEXT);
                while(1) { wait_vblank(); }
            }
        }
    }
    return 0;
}
