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

typedef struct { int year, month, day, hour, minute, second; } RtcTime;

static int bcd2dec(unsigned char b) {
    return ((b >> 4) & 0x0F) * 10 + (b & 0x0F);
}
static void rtc_delay(void) { for (volatile int i = 0; i < 48; i++); }

static void rtc_write_bit(unsigned char bit) {
    volatile unsigned short *r = (volatile unsigned short*)0x04000138;
    *r = (unsigned short)(0x0A | (bit ? 0x02 : 0x00)); rtc_delay();
    *r = (unsigned short)(0x0E | (bit ? 0x02 : 0x00)); rtc_delay();
}
static unsigned char rtc_read_byte(void) {
    volatile unsigned short *r = (volatile unsigned short*)0x04000138;
    unsigned char val = 0;
    for (int i = 0; i < 8; i++) {
        *r = 0x04; rtc_delay();
        *r = 0x0C; rtc_delay();
        val >>= 1;
        if (*r & 0x02) val |= 0x80;
    }
    return val;
}
static void rtc_write_byte(unsigned char data) {
    for (int i = 0; i < 8; i++) rtc_write_bit((data >> i) & 1);
}
static void rtc_read(RtcTime *t) {
    volatile unsigned short *r = (volatile unsigned short*)0x04000138;
    *r = 0x06; rtc_delay();
    rtc_write_byte(0x65);
    unsigned char y  = rtc_read_byte();
    unsigned char mo = rtc_read_byte();
    unsigned char d  = rtc_read_byte();
    rtc_read_byte();
    unsigned char h  = rtc_read_byte();
    unsigned char mi = rtc_read_byte();
    rtc_read_byte();
    *r = 0x02; rtc_delay();
    t->year   = 2000 + bcd2dec(y);
    t->month  = bcd2dec(mo & 0x1F);
    t->day    = bcd2dec(d  & 0x3F);
    t->hour   = bcd2dec(h  & 0x3F);
    t->minute = bcd2dec(mi & 0x7F);
}
static void fmt2d(char *d, int n) {
    d[0] = '0' + (n / 10) % 10;
    d[1] = '0' + n % 10;
}
static void fmt_datetime(char *buf, const RtcTime *t) {
    fmt2d(buf+0, t->day);   buf[2]='/';
    fmt2d(buf+3, t->month); buf[5]='/';
    buf[6]='0'+(t->year/1000)%10; buf[7]='0'+(t->year/100)%10;
    buf[8]='0'+(t->year/10)%10;   buf[9]='0'+t->year%10;
    buf[10]=' '; buf[11]='|'; buf[12]=' ';
    fmt2d(buf+13, t->hour);   buf[15]=':';
    fmt2d(buf+16, t->minute); buf[18]='\0';
}

static void init_audio(void) {
    REG_SOUNDCNT  = 0x807F;
    REG_SOUNDBIAS = 0x0200;
}
static void beep(int freq) {
    unsigned short v = 51160;
    if (freq==220) v=35160; else if (freq==500) v=53000;
    else if (freq==600) v=55212; else if (freq==880) v=59180;
    else if (freq==1200) v=61212;
    REG_CH0_TMR = v;
    REG_CH0_CNT = 0x877F0000;
    for (int i = 0; i < 10; i++) wait_vblank();
    REG_CH0_CNT = 0;
}

static void draw_divider(void) {
    draw_hline(VRAM_TOP,    24, COLOR_TEXT);
    draw_hline(VRAM_BOTTOM, 24, COLOR_TEXT);
}

static void draw_progress_frame(void) {
    draw_rect_outline(VRAM_TOP, 48, 100, 208, 112, COLOR_TEXT);
}
static void update_progress(int p) {
    fill_rect(VRAM_TOP, 50, 102, 50 + (p * 156) / 100, 110, COLOR_SELECT);
}

#define PIN_Y    90
#define PIN_X0   40
#define PIN_STEP 48

static void draw_pin_display(int ndigits) {
    fill_rect(VRAM_TOP, PIN_X0 - 2, PIN_Y - 2,
              PIN_X0 + 4 * PIN_STEP + 4, PIN_Y + 10, COLOR_BG);
    for (int i = 0; i < 4; i++) {
        int bx = PIN_X0 + i * PIN_STEP;
        if (i < ndigits)
            print_text("[*]", bx, PIN_Y, VRAM_TOP, COLOR_BLACK);
        else
            print_text("[_]", bx, PIN_Y, VRAM_TOP, COLOR_BLACK);
    }
}

static const char  g_chars[12][4] = {
    "1","2","3","4","5","6","7","8","9","-","0","OK"
};
static const int g_x[12] = {
    72,128,184, 72,128,184, 72,128,184, 72,128,184
};
static const int g_y[12] = {
    40,40,40, 70,70,70, 100,100,100, 130,130,130
};

static void draw_grid(int active) {
    for (int i = 0; i < 12; i++) {
        unsigned short col = (i == active) ? COLOR_SELECT : COLOR_TEXT;
        print_text("[   ]", g_x[i] - 8, g_y[i], VRAM_BOTTOM, col);
        print_text(g_chars[i], g_x[i], g_y[i], VRAM_BOTTOM, col);
    }
}

int main(void) {
    video_init();
    init_audio();
    wait_vblank();

    print_text("Luish Factory Setup",    8,  8, VRAM_TOP, COLOR_TEXT);
    draw_divider();
    print_text("Loading Luish files...", 48, 70, VRAM_TOP, COLOR_TEXT);
    draw_progress_frame();

    char pstr[6];
    for (int p = 0; p <= 100; p++) {
        wait_vblank();
        update_progress(p);
        if      (p < 10)  { pstr[0]='0'+p; pstr[1]='%'; pstr[2]='\0'; }
        else if (p < 100) { pstr[0]='0'+p/10; pstr[1]='0'+p%10; pstr[2]='%'; pstr[3]='\0'; }
        else              { pstr[0]='1'; pstr[1]='0'; pstr[2]='0'; pstr[3]='%'; pstr[4]='\0'; }
        fill_rect(VRAM_TOP, 112, 130, 152, 138, COLOR_BG);
        print_text(pstr, 112, 130, VRAM_TOP, COLOR_SELECT);
    }
    beep(880);

    video_init();
    draw_divider();
    print_text("Security Authorization",  8,  8, VRAM_TOP,    COLOR_TEXT);
    print_text("Enter System PIN code:", 32, 55, VRAM_TOP,    COLOR_BLACK);
    print_text("PIN Keypad",             80,  8, VRAM_BOTTOM,  COLOR_TEXT);

    const int correct[4] = {3, 5, 5, 0};
    int buf[4] = {-1,-1,-1,-1};
    int slot = 0, ndigits = 0;

    draw_pin_display(0);
    draw_grid(slot);

    unsigned short prev_keys = REG_KEYINPUT;

    int authed = 0;
    while (!authed) {
        wait_vblank();
        unsigned short cur  = REG_KEYINPUT;
        unsigned short hits = (prev_keys ^ cur) & ~cur;
        prev_keys = cur;

        if (hits & KEY_RIGHT) { if (slot%3 < 2)  slot++;  draw_grid(slot); }
        if (hits & KEY_LEFT)  { if (slot%3 > 0)  slot--;  draw_grid(slot); }
        if (hits & KEY_DOWN)  { if (slot < 9)    slot+=3; draw_grid(slot); }
        if (hits & KEY_UP)    { if (slot >= 3)   slot-=3; draw_grid(slot); }

        if (hits & KEY_A) {
            if (slot == 11) {
                if (ndigits == 4 &&
                    buf[0]==correct[0] && buf[1]==correct[1] &&
                    buf[2]==correct[2] && buf[3]==correct[3]) {
                    authed = 1;
                } else {
                    beep(220);
                    ndigits = 0;
                    for (int i=0;i<4;i++) buf[i]=-1;
                    draw_pin_display(0);
                }
            } else if (slot == 9) {
                ndigits = 0;
                for (int i=0;i<4;i++) buf[i]=-1;
                draw_pin_display(0);
            } else {
                int val = (slot == 10) ? 0 : (slot + 1);
                if (ndigits < 4) {
                    beep(600);
                    buf[ndigits++] = val;
                    draw_pin_display(ndigits);
                }
            }
        }
    }
    beep(1200);

    video_init();
    draw_divider();

    RtcTime now;
    rtc_read(&now);
    char dtbuf[20];
    fmt_datetime(dtbuf, &now);

    print_text("LUISH",  8,  8, VRAM_TOP,    COLOR_TEXT);
    print_text(dtbuf,           88,  8, VRAM_TOP,    COLOR_SELECT);
    print_text("Welcome back.", 48, 60, VRAM_TOP,    COLOR_TEXT);

    print_text("Select an option:", 48, 36, VRAM_BOTTOM, COLOR_TEXT);
    print_text("1. Hardware Specs", 24, 60, VRAM_BOTTOM, COLOR_SELECT);
    print_text("2. Reset Firmware", 24, 90, VRAM_BOTTOM, COLOR_TEXT);
    print_text("3. Exit Shell",     24,120, VRAM_BOTTOM, COLOR_TEXT);

    int menu = 0;
    while (1) {
        wait_vblank();
        unsigned short cur  = REG_KEYINPUT;
        unsigned short hits = (prev_keys ^ cur) & ~cur;
        prev_keys = cur;

        if (hits & KEY_DOWN) {
            if (++menu > 2) menu = 0;
            print_text("1. Hardware Specs", 24, 60, VRAM_BOTTOM, menu==0?COLOR_SELECT:COLOR_TEXT);
            print_text("2. Reset Firmware", 24, 90, VRAM_BOTTOM, menu==1?COLOR_SELECT:COLOR_TEXT);
            print_text("3. Exit Shell",     24,120, VRAM_BOTTOM, menu==2?COLOR_SELECT:COLOR_TEXT);
            beep(500);
        }
        if (hits & KEY_UP) {
            if (--menu < 0) menu = 2;
            print_text("1. Hardware Specs", 24, 60, VRAM_BOTTOM, menu==0?COLOR_SELECT:COLOR_TEXT);
            print_text("2. Reset Firmware", 24, 90, VRAM_BOTTOM, menu==1?COLOR_SELECT:COLOR_TEXT);
            print_text("3. Exit Shell",     24,120, VRAM_BOTTOM, menu==2?COLOR_SELECT:COLOR_TEXT);
            beep(500);
        }

        if (hits & KEY_A) {
            if (menu == 0) {
                video_init();
                draw_divider();
                print_text("Hardware Info",             8,   8, VRAM_TOP,    COLOR_TEXT);
                print_text("Platform: Nintendo DS",    16,  36, VRAM_TOP,    COLOR_TEXT);
                print_text("ARM9: 67MHz ARM946E-S",    16,  52, VRAM_TOP,    COLOR_TEXT);
                print_text("ARM7: 33MHz ARM7TDMI",     16,  68, VRAM_TOP,    COLOR_TEXT);
                print_text("RAM:  4MB + 256KB",        16,  84, VRAM_TOP,    COLOR_TEXT);
                print_text("VRAM: 656KB (A-I)",        16, 100, VRAM_TOP,    COLOR_TEXT);
                print_text("Hardware Detail",          16,   8, VRAM_BOTTOM, COLOR_TEXT);
                print_text("Display: 2x256x192 TFT",   16,  36, VRAM_BOTTOM, COLOR_TEXT);
                print_text("WiFi: IEEE 802.11b",       16,  52, VRAM_BOTTOM, COLOR_TEXT);
                print_text("SPI: RTC + Firmware",      16,  68, VRAM_BOTTOM, COLOR_TEXT);
                print_text("DMA: 4ch ARM9+2ch ARM7",   16,  84, VRAM_BOTTOM, COLOR_TEXT);
                print_text("VRAM: DIRECT LCD MODE",    16, 100, VRAM_BOTTOM, COLOR_TEXT);
                print_text("STATUS: OPERATIONAL",      16, 116, VRAM_BOTTOM, COLOR_SELECT);
                while (1) { wait_vblank(); }
            } else {
                video_init();
                draw_divider();
                print_text("System Halt",       8,  8, VRAM_TOP,    COLOR_TEXT);
                print_text("Operation halted.", 48, 80, VRAM_TOP,    COLOR_TEXT);
                print_text("Power off the DS.", 24, 80, VRAM_BOTTOM, COLOR_TEXT);
                while (1) { wait_vblank(); }
            }
        }
    }

    return 0;
}
