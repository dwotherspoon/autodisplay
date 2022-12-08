MCU = IMXRT1062
MCU_LD = imxrt1062_t41.ld
MCU_DEF = ARDUINO_TEENSY41

CPU_OPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

TEST_CC = gcc
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -Wall -Wextra -Wpedantic -O1 $(CPU_OPTIONS) -ffunction-sections -fdata-sections -Isrc/include
LIBS = -larm_cortexM7lfsp_math -lm
LDFLAGS = -Os -Wl,--gc-sections,--relax $(SPECS) $(CPU_OPTIONS) -T$(MCU_LD)

MAIN_EXECNAME = rom.hex
TEST_EXECNAME = test
TEST_SRCS = src/test.c src/displays/display.c src/displays/display_sdl.c src/image/image.c
TEST_CFLAGS = -Wall -Wextra -Wpedantic -O1 -Isrc/include

DISPLAY_OBJS = src/displays/display.o
GAUGE_OBJS = src/gauges/gauge.o src/gauges/gauge_test.o src/gauges/gauge_dial.o
INPUT_OBJS = src/inputs/input.o
IMAGE_OBJS = src/image/image.o

all: main test
	@echo "Build complete."

main: $(GAUGE_OBJS) $(DISPLAY_OBJS) $(INPUT_OBJS) $(IMAGE_OBJS)
	$(CC) $(CFLAGS) src/main.c $(GAUGE_OBJS) -o $(TEST_EXECNAME)

test:
	$(TEST_CC) -DTEST_BUILD $(TEST_SRCS) $(TEST_CFLAGS) $(shell pkg-config --cflags --libs sdl2) -o $(TEST_EXECNAME)

.PHONY: clean
clean:
	rm -f $(MAIN_EXECNAME) $(TEST_EXECNAME) $(GAUGE_OBJS) $(INPUT_OBJS) $(IMAGE_OBJS)