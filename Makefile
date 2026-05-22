DEVKITARM = /opt/devkitpro/devkitARM

CC      = $(DEVKITARM)/bin/arm-none-eabi-gcc
AS      = $(DEVKITARM)/bin/arm-none-eabi-as
LD      = $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY = $(DEVKITARM)/bin/arm-none-eabi-objcopy
NDSTOOL = /opt/devkitpro/tools/bin/ndstool

CFLAGS  = -mthumb-interwork -marm -O2 -Wall -I. -I./data -I./wmf
ASFLAGS = -mthumb-interwork

OBJS = crt0.o main.o data/video.o

all: main.nds

main.nds: main.elf
	$(OBJCOPY) -O binary main.elf arm9.bin
	touch arm7.bin
	
	@echo "LUISH" > banner.txt
	@echo "Luish for Nintendo DS" >> banner.txt # Japanese Entry
	@echo "Luish for Nintendo DS" >> banner.txt # English Entry
	@echo "Luish for Nintendo DS" >> banner.txt # French Entry
	@echo "Luish for Nintendo DS" >> banner.txt # German Entry
	@echo "Luish for Nintendo DS" >> banner.txt # Italian Entry
	@echo "Luish for Nintendo DS" >> banner.txt # Spanish Entry
	
	$(NDSTOOL) -m banner.bin -t banner.txt
	
	$(NDSTOOL) -c main.nds -9 arm9.bin -7 arm7.bin -d nitrofiles -b banner.bin
	
	rm -f arm9.bin arm7.bin banner.txt banner.bin

main.elf: $(OBJS)
	$(LD) -T nds.ld $(OBJS) -o main.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

crt0.o: crt0.s
	$(AS) $(ASFLAGS) crt0.s -o crt0.o

clean:
	rm -f *.o data/*.o *.elf *.bin *.nds
