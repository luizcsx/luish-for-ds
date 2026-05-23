DEVKITPRO ?= /opt/devkitpro
DEVKITARM  ?= $(DEVKITPRO)/devkitARM

export PATH := $(DEVKITARM)/bin:$(PATH)

PREFIX  = arm-none-eabi-
CC      = $(PREFIX)gcc
AS      = $(PREFIX)as
LD      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
NDSTOOL = $(DEVKITPRO)/tools/bin/ndstool

LIBNDS  = $(DEVKITPRO)/libnds

ARCH    = -mthumb-interwork -marm -mcpu=arm946e-s -mtune=arm946e-s

CFLAGS9 = $(ARCH) -O2 -Wall \
           -I. -Idata \
           -I$(LIBNDS)/include \
           -fomit-frame-pointer \
           -DARM9

CFLAGS7 = -mthumb-interwork -marm -mcpu=arm7tdmi -mtune=arm7tdmi \
           -O2 -Wall \
           -I$(LIBNDS)/include \
           -fomit-frame-pointer \
           -DARM7

LDFLAGS9 = $(ARCH) \
            -specs=$(DEVKITARM)/arm-none-eabi/lib/ds_arm9.specs \
            -L$(LIBNDS)/lib

LDFLAGS7 = -mthumb-interwork -marm -mcpu=arm7tdmi \
            -specs=$(DEVKITARM)/arm-none-eabi/lib/ds_arm7.specs \
            -L$(LIBNDS)/lib

OBJS9 = main.o data/video.o

all: main.nds

main.nds: arm9.bin arm7.bin
	$(NDSTOOL) -c main.nds -9 arm9.bin -7 arm7.bin -g LUSH 0000 "Luish"
	rm -f arm9.bin arm7.bin

arm9.bin: arm9.elf
	$(OBJCOPY) -O binary $< $@

arm9.elf: $(OBJS9)
	$(LD) $(LDFLAGS9) $(OBJS9) -lnds9 -o $@

arm7.bin: arm7.elf
	$(OBJCOPY) -O binary $< $@

arm7.elf: arm7.o
	$(LD) $(LDFLAGS7) arm7.o -lnds7 -o $@

arm7.o: arm7.c
	$(CC) $(CFLAGS7) -c arm7.c -o arm7.o

data/video.o: data/video.c data/video.h
	$(CC) $(CFLAGS9) -c data/video.c -o data/video.o

%.o: %.c
	$(CC) $(CFLAGS9) -c $< -o $@

clean:
	rm -f *.o data/*.o *.elf *.bin *.nds
