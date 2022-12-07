MCU = IMXRT1062
MCU_LD = imxrt1062_t41.ld
MCU_DEF = ARDUINO_TEENSY41

CPU_OPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -Wall -Wextra -Wpedantic -O1 $(CPU_OPTIONS) -ffunction-sections -fdata-sections -Isrc/include
LIBS = -larm_cortexM7lfsp_math -lm
LDFLAGS = -Os -Wl,--gc-sections,--relax $(SPECS) $(CPU_OPTIONS) -T$(MCU_LD)

EXECNAME = rom.hex

all: src/main.o
	@echo "Build complete."

.PHONY: clean
clean:
	rm -f $(EXECNAME)
