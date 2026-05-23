.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Defina DEVKITARM no ambiente: export DEVKITARM=<caminho>/devkitARM")
endif

export TARGET := luish

.PHONY: all arm7 arm9 clean

all: arm7 arm9
	@ndstool -c $(TARGET).nds \
	         -9 arm9/$(TARGET).arm9.bin \
	         -7 arm7/$(TARGET).arm7.bin \
	         -g LUSH 0000 "Luish"
	@echo "Done: $(TARGET).nds"

arm7:
	@$(MAKE) -C arm7

arm9:
	@$(MAKE) -C arm9

clean:
	@$(MAKE) -C arm7 clean
	@$(MAKE) -C arm9 clean
	@rm -f $(TARGET).nds
