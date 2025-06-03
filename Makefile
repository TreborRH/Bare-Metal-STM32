# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy

# Ziel-MCU
MCU = cortex-m3
DEFS = -DSTM32L152xE -DNUCLEO_L152RE -DSTM32L1 -DSTM32 -DSTM32L152RETx

# Includes
INCLUDES = -IInc

# Dateien (unbedingt anpassen, falls neue Quellen hinzukommen!)
SRCS = Src/main.c Inc/gpio.c Inc/interrupt.c Inc/timer.c Src/syscalls.c Src/sysmem.c
ASMS = Startup/startup_stm32l152retx.s
OBJS = $(SRCS:.c=.o) $(ASMS:.s=.o)
LDSCRIPT = STM32L152RETX_FLASH.ld

# Flags
CFLAGS = -mcpu=$(MCU) -mthumb -O2 -Wall $(DEFS) $(INCLUDES)
AFLAGS = -mcpu=$(MCU) -mthumb
LDFLAGS = -T$(LDSCRIPT) -nostartfiles -mcpu=$(MCU) -mthumb

TARGET = Bare-Metal-STM32

all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O ihex $@ $(TARGET).hex
	$(OBJCOPY) -O binary $@ $(TARGET).bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(AFLAGS) -c $< -o $@

clean:
	rm -f Inc/*.o Src/*.o Startup/*.o *.elf *.bin *.hex

flash: $(TARGET).elf
	st-flash write $(TARGET).bin 0x8000000

.PHONY: all clean flash
