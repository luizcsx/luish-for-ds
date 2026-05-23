DEVKITARM = /opt/devkitpro/devkitARM

CC      = $(DEVKITARM)/bin/arm-none-eabi-gcc
AS      = $(DEVKITARM)/bin/arm-none-eabi-as
LD      = $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY = $(DEVKITARM)/bin/arm-none-eabi-objcopy
NDSTOOL = /opt/devkitpro/tools/bin/ndstool

CFLAGS  = -mthumb-interwork -marm -O2 -Wall -I. -I./data -I./wmf
ASFLAGS = -mthumb-interwork

LIBGCC  = $(DEVKITARM)/lib/gcc/arm-none-eabi/$(shell $(CC) -dumpversion)

all: main.nds

video.o:
	@if [ -f video.c ]; then \
		$(CC) $(CFLAGS) -c video.c -o video.o; \
	else \
		$(CC) $(CFLAGS) -c data/video.c -o video.o; \
	fi

font.o: font.c
	$(CC) $(CFLAGS) -c font.c -o font.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

crt0.o: crt0.s
	$(AS) $(ASFLAGS) crt0.s -o crt0.o

arm7.bin: arm7.c
	$(CC) $(CFLAGS) -marm -mcpu=arm7tdmi -c arm7.c -o arm7.o
	$(LD) -Ttext 0x03800000 arm7.o -lgcc -L$(LIBGCC) -o arm7.elf
	$(OBJCOPY) -O binary arm7.elf arm7.bin

main.elf: crt0.o main.o video.o font.o
	$(LD) -T nds.ld crt0.o main.o video.o font.o -lgcc -L$(LIBGCC) -o main.elf

main.nds: main.elf arm7.bin
	$(OBJCOPY) -O binary main.elf arm9.bin
	$(NDSTOOL) -c main.nds -9 arm9.bin -7 arm7.bin -d nitrofiles -g LUSH 01 "Luish"
	rm -f arm9.bin arm7.bin arm7.elf arm7.o crt0.o main.o video.o font.o main.elf
