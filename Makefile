.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Defina DEVKITARM: export DEVKITARM=/opt/devkitpro/devkitARM")
endif

include $(DEVKITARM)/ds_rules

TARGET   := luish
BUILD    := build
SOURCES  := source
INCLUDES := include
DATA     :=
GRAPHICS :=
NITRO    :=

ARCH := -march=armv5te -mtune=arm946e-s

CFLAGS   := -g -Wall -O2 -ffunction-sections -fdata-sections \
             $(ARCH) $(INCLUDE) -DARM9

CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS  := -g $(ARCH)
LDFLAGS   = -specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS    := -lnds9
LIBDIRS := $(LIBNDS)

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT  := $(CURDIR)/$(TARGET)
export TOPDIR  := $(CURDIR)

export VPATH := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                $(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR := $(CURDIR)/$(BUILD)

# Coleta todos os .c da pasta source/, EXCETO arm7.c
CFILES_ALL := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CFILES
