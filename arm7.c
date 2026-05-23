#define REG_POWERCNT_7  *(volatile unsigned short*)0x04000304

int main(void) {
    REG_POWERCNT_7 |= 0x0001; 

    while (1) {
        __asm__("swi 0x060000");
    }
    return 0;
}
