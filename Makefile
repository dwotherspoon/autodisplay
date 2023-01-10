MCU = IMXRT1062
MCU_LD = src/boards/imxrt1062_t41.ld
MCU_DEF = ARDUINO_TEENSY41

OPTIONS =  -D__$(MCU)__
CPU_OPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

TEST_CC = gcc
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CFLAGS = -Wall -Wextra -Wpedantic -O0 $(CPU_OPTIONS) $(OPTIONS) -MMD -ffunction-sections -fdata-sections -Isrc/include
#LIBS = -larm_cortexM7lfsp_math -lm
LDFLAGS = -Os -Wl,--gc-sections,--relax $(CPU_OPTIONS) -T$(MCU_LD)

TEST_EXECNAME = test
TEST_SRCS = src/test.c src/debug.c src/displays/display.c src/displays/display_sdl.c src/image/image.c src/image/image_formats.c
TEST_CFLAGS = -Wall -Wextra -Wpedantic -O1 -Isrc/include

TARGET = autodisplay
MAIN_OBJS = src/main.o
BOARD_OBJS = src/boards/imxrt1062.o
DISPLAY_OBJS = src/displays/display.o src/displays/display_gc9a01a.o
GAUGE_OBJS = src/gauges/gauge.o src/gauges/gauge_test.o src/gauges/gauge_dial.o
INPUT_OBJS = src/inputs/input.o src/inputs/input_bme280.o
IMAGE_OBJS = src/image/image.o src/image/image_formats.o

all: $(TARGET).hex test
	@echo "Build complete."

$(TARGET).elf: $(BOARD_OBJS) $(MAIN_OBJS) $(GAUGE_OBJS) $(DISPLAY_OBJS) $(INPUT_OBJS) $(IMAGE_OBJS) $(MCU_LD)
	$(CC) $(LDFLAGS) -o $@ $(MAIN_OBJS) $(GAUGE_OBJS) $(DISPLAY_OBJS) $(INPUT_OBJS) $(IMAGE_OBJS) $(LIBS)

%.hex: %.elf
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@

install: $(TARGET).hex
	@echo "Install to teensy"

main: $(GAUGE_OBJS) $(DISPLAY_OBJS) $(INPUT_OBJS) $(IMAGE_OBJS)
	$(CC) $(CFLAGS) src/main.c $(GAUGE_OBJS) -o $(TEST_EXECNAME)

test:
	$(TEST_CC) -DTEST_BUILD -DDEBUG_EN $(TEST_SRCS) $(TEST_CFLAGS) $(shell pkg-config --cflags --libs sdl2) -o $(TEST_EXECNAME)

.PHONY: clean
clean:
	rm -f $(TARGET).hex $(TARGET).elf $(MAIN_OBJS) $(TEST_EXECNAME) $(GAUGE_OBJS) $(INPUT_OBJS) $(IMAGE_OBJS) $(DISPLAY_OBJS)
