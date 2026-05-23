#include "video.h"

#define REG_KEYINPUT    *(volatile unsigned short*)0x04000130
#define REG_SOUNDCNT    *(volatile unsigned short*)0x04000500
#define REG_SOUNDBIAS   *(volatile unsigned short*)0x04000504
#define REG_CH0_CNT     *(volatile unsigned int*)0x04000400
#define REG_CH0_TMR     *(volatile unsigned short*)0x04000408

#define KEY_UP          (1 << 6)
#define KEY_DOWN        (1 << 7)
#define KEY_LEFT        (1 << 5)
#define KEY_RIGHT       (1 << 4)
#define KEY_A           (1 << 0)

static void init_audio(void) {
    REG_SOUNDCNT  = 0x807F;
    REG_SOUNDBIAS = 0x0200;
}

static void beep(int frequency) {
    unsigned short timer_val = 51160;
    if (frequency == 220)  timer_val = 35160;
    if (frequency == 500)  timer_val = 53000;
    if (frequency == 600)  timer_val = 55212;
    if (frequency == 880)  timer_val = 59180;
    if (frequency == 1200) timer_val = 61212;

    REG_CH0_TMR = timer_val;
    REG_CH0_CNT = 0x877F0000;
    for (int i = 0; i < 10; i++) wait_vblank();
    REG_CH0_CNT = 0x00000000;
}

static void draw_header_divider(void) {
    draw_hline(VRAM_TOP,    24, COLOR_TEXT);
    draw_hline(VRAM_BOTTOM, 24, COLOR_TEXT);
}

static void draw_progress_frame(void) {
    draw_rect_outline(VRAM_TOP, 48, 100, 208, 112, COLOR_TEXT);
}

static void update_progress(int percent) {
    int w = (percent * 156) / 100;
    fill_rect(VRAM_TOP, 50, 102, 50 + w, 110, COLOR_SELECT);
}

static const char grid_chars[12][4] = {
    "1","2","3",
    "4","5","6",
    "7","8","9",
    "-","0","OK"
};
static const int grid_x[12] = { 64,120,176, 64,120,176, 64,120,176, 64,120,176 };
static const int grid_y[12] = { 60,60,60, 90,90,90, 120,120,120, 150,150,150 };

static void draw_pin_grid(int active) {
    for (int i = 0; i < 12; i++) {
        unsigned short col = (i == active) ? COLOR_SELECT : COLOR_TEXT;
        print_text("[   ]", grid_x[i] - 8, grid_y[i], VRAM_BOTTOM, col);
        print_text(grid_chars[i], grid_x[i], grid_y[i], VRAM_BOTTOM, col);
    }
}

int main(void) {
    video_init();
    init_audio();
    wait_vblank();

    print_text("Luish Factory Setup",   8,  8, VRAM_TOP, COLOR_TEXT);
    draw_header_divider();
    print_text("Loading Luish files...",48, 70, VRAM_TOP, COLOR_TEXT);
    draw_progress_frame();

    char pstr[5];
    for (int p = 0; p <= 100; p++) {
        wait_vblank();
        update_progress(p);

        if (p < 10) {
            pstr[0] = '0' + p;  pstr[1] = '%'; pstr[2] = '\0';
        } else if (p < 100) {
            pstr[0] = '0' + p / 10;
            pstr[1] = '0' + p % 10;
            pstr[2] = '%'; pstr[3] = '\0';
        } else {
            pstr[0]='1'; pstr[1]='0'; pstr[2]='0'; pstr[3]='%'; pstr[4]='\0';
        }

        fill_rect(VRAM_TOP, 112, 130, 148, 138, COLOR_BG);
        print_text(pstr, 112, 130, VRAM_TOP, COLOR_SELECT);
    }

    beep(880);

    video_init();
    draw_header_divider();
    print_text("Security Authorization",  8,  8, VRAM_TOP, COLOR_TEXT);
    print_text("Enter System PIN code:", 48, 60, VRAM_TOP, COLOR_TEXT);
    print_text("[ _ ] [ _ ] [ _ ] [ _ ]",48, 90, VRAM_TOP, COLOR_TEXT);

    int slot = 0, ndigits = 0;
    int buf[4]             = {-1,-1,-1,-1};
    const int correct[4]   = { 1, 2, 3, 4};

    unsigned short prev_keys = REG_KEYINPUT;
    draw_pin_grid(slot);

    int authed = 0;
    while (!authed) {
        wait_vblank();
        unsigned short cur  = REG_KEYINPUT;
        unsigned short hits = (prev_keys ^ cur) & ~cur;
        prev_keys = cur;

        if (hits & KEY_RIGHT) { if (slot % 3 < 2) slot++; draw_pin_grid(slot); }
        if (hits & KEY_LEFT)  { if (slot % 3 > 0) slot--; draw_pin_grid(slot); }
        if (hits & KEY_DOWN)  { if (slot < 9) slot += 3;  draw_pin_grid(slot); }
        if (hits & KEY_UP)    { if (slot >= 3) slot -= 3; draw_pin_grid(slot); }

        if (hits & KEY_A) {
            if (slot == 11) {
                /* OK */
                if (ndigits == 4 &&
                    buf[0]==correct[0] && buf[1]==correct[1] &&
                    buf[2]==correct[2] && buf[3]==correct[3]) {
                    authed = 1;
                } else {
                    beep(220);
                    ndigits = 0;
                    for (int i=0;i<4;i++) buf[i]=-1;
                    fill_rect(VRAM_TOP, 48, 90, 230, 98, COLOR_BG);
                    print_text("[ _ ] [ _ ] [ _ ] [ _ ]", 48, 90, VRAM_TOP, COLOR_TEXT);
                }
            } else if (slot == 9) {
                ndigits = 0;
                for (int i=0;i<4;i++) buf[i]=-1;
                fill_rect(VRAM_TOP, 48, 90, 230, 98, COLOR_BG);
                print_text("[ _ ] [ _ ] [ _ ] [ _ ]", 48, 90, VRAM_TOP, COLOR_TEXT);
            } else {
                int val = (slot == 10) ? 0 : (slot + 1);
                if (ndigits < 4) {
                    beep(600);
                    buf[ndigits] = val;
                    print_text("*", 56 + ndigits * 40, 90, VRAM_TOP, COLOR_SELECT);
                    ndigits++;
                }
            }
        }
    }

    beep(1200);
    video_init();
    draw_header_divider();

    print_text("Luish OS v1.0",      8,   8, VRAM_TOP, COLOR_TEXT);
    print_text("22/05/2026 - 23:33",104,   8, VRAM_TOP, COLOR_SELECT);
    print_text("System Active.",     48,  60, VRAM_TOP, COLOR_TEXT);

    print_text("1. Hardware Specifications", 24,  60, VRAM_BOTTOM, COLOR_SELECT);
    print_text("2. Reset Firmware Settings", 24,  90, VRAM_BOTTOM, COLOR_TEXT);
    print_text("3. Exit Console Shell",      24, 120, VRAM_BOTTOM, COLOR_TEXT);

    int menu = 0;
    while (1) {
        wait_vblank();
        unsigned short cur  = REG_KEYINPUT;
        unsigned short hits = (prev_keys ^ cur) & ~cur;
        prev_keys = cur;

        if (hits & KEY_DOWN) {
            menu++; if (menu > 2) menu = 0;
            print_text("1. Hardware Specifications",24, 60,VRAM_BOTTOM,(menu==0)?COLOR_SELECT:COLOR_TEXT);
            print_text("2. Reset Firmware Settings",24, 90,VRAM_BOTTOM,(menu==1)?COLOR_SELECT:COLOR_TEXT);
            print_text("3. Exit Console Shell",     24,120,VRAM_BOTTOM,(menu==2)?COLOR_SELECT:COLOR_TEXT);
            beep(500);
        }
        if (hits & KEY_UP) {
            menu--; if (menu < 0) menu = 2;
            print_text("1. Hardware Specifications",24, 60,VRAM_BOTTOM,(menu==0)?COLOR_SELECT:COLOR_TEXT);
            print_text("2. Reset Firmware Settings",24, 90,VRAM_BOTTOM,(menu==1)?COLOR_SELECT:COLOR_TEXT);
            print_text("3. Exit Console Shell",     24,120,VRAM_BOTTOM,(menu==2)?COLOR_SELECT:COLOR_TEXT);
            beep(500);
        }

        if (hits & KEY_A) {
            if (menu == 0) {
                video_init();
                draw_header_divider();
                print_text("Hardware Diagnostics",      8,   8, VRAM_TOP, COLOR_TEXT);
                print_text("CPU: ARM946E-S & ARM7TDMI",16,  50, VRAM_BOTTOM, COLOR_TEXT);
                print_text("BUS ENGINE: INTERNAL PSG",  16,  70, VRAM_BOTTOM, COLOR_TEXT);
                print_text("VRAM BLOCK MAP: DIRECT LCD",16,  90, VRAM_BOTTOM, COLOR_TEXT);
                print_text("STATUS: OPERATIONAL",       16, 110, VRAM_BOTTOM, COLOR_SELECT);
                while (1) { wait_vblank(); }
            } else {
                video_init();
                draw_header_divider();
                print_text("Operation halted.", 48, 80, VRAM_TOP, COLOR_TEXT);
                while (1) { wait_vblank(); }
            }
        }
    }

    return 0;
}
