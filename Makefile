DEVKITARM = /opt/devkitpro/devkitARM

CC      = $(DEVKITARM)/bin/arm-none-eabi-gcc
AS      = $(DEVKITARM)/bin/arm-none-eabi-as
LD      = $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY = $(DEVKITARM)/bin/arm-none-eabi-objcopy
NDSTOOL = /opt/devkitpro/tools/bin/ndstool

CFLAGS  = -mthumb-interwork -marm -O2 -Wall
ASFLAGS = -mthumb-interwork

all: main.nds

main.nds: main.elf
	$(OBJCOPY) -O binary main.elf arm9.bin
	touch arm7.bin
	mkdir -p nitrofiles
	$(NDSTOOL) -c main.nds -9 arm9.bin -7 arm7.bin -d nitrofiles -h "Luish;Productivity and Creation System;Luiz Miguel"

main.elf: crt0.o main.o
	$(LD) -T nds.ld crt0.o main.o -o main.elf

crt0.o: crt0.s
	$(AS) $(ASFLAGS) crt0.s -o crt0.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f *.o *.elf *.bin *.nds
