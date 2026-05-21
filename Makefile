DEVKITARM = /opt/devkitpro/devkitARM
PREFIX  = $(DEVKITARM)/bin/arm-none-eabi-
CC      = $(PREFIX)gcc
AS      = $(PREFIX)as
LD      = $(PREFIX)ld
OBJCOPY = $(PREFIX)objcopy
NDSTOOL = /opt/devkitpro/tools/bin/ndstool

CFLAGS  = -mthumb-interwork -marm -O2 -Wall
ASFLAGS = -mthumb-interwork
LDFLAGS = -T nds.ld

all: luish.nds

luish.nds: main.elf
	$(OBJCOPY) -O binary main.elf arm9.bin
	touch arm7.bin
	$(NDSTOOL) -c luish.nds -9 arm9.bin -7 arm7.bin
	rm -f arm9.bin arm7.bin main.elf main.o crt0.o

main.elf: crt0.o main.o
	$(LD) $(LDFLAGS) crt0.o main.o -o main.elf

crt0.o: crt0.s
	$(AS) $(ASFLAGS) crt0.s -o crt0.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o *.elf *.nds
