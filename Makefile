# Toolchain configuration
CC       = avr-gcc
OBJCOPY  = avr-objcopy
SIZE     = avr-size
RM       = rm -rf
MKDIR    = mkdir -p

# Project structure
BUILD_DIR        = build
SRC_DIR          = src
FIRMWARE_NAME    = firmware
TARGET_HEX       = $(BUILD_DIR)/$(FIRMWARE_NAME).hex
TARGET_ELF       = $(BUILD_DIR)/$(FIRMWARE_NAME).elf

# MCU configuration
MCU              = atmega328p
F_CPU            = 16000000UL

# Compiler/linker flags
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS += -Wall -Os
CFLAGS += -MMD -MP
CFLAGS += -I${AVR_PATH}/include

LDFLAGS = -mmcu=$(MCU)

# AVRDUDE configuration
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT       = ch340
AVRDUDE_FLAGS      = -c $(AVRDUDE_PROGRAMMER) -p $(MCU:atmega%=m%) -P $(AVRDUDE_PORT)

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

.PHONY: all clean flash size

all: $(TARGET_HEX)

$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

$(TARGET_ELF): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@$(MKDIR) $(BUILD_DIR)

-include $(DEPS)

size: $(TARGET_ELF)
	$(SIZE) $<

flash: $(TARGET_HEX)
	avrdude $(AVRDUDE_FLAGS) -U flash:w:$<:i

clean:
	$(RM) $(BUILD_DIR)
