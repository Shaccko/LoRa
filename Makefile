CFLAGS  ?=  -W -Wall -Wextra -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections -I. \
            -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = main.c rcc.c startup.c uart.c spi.c LoRa.c syscalls.c exti.c
HEADER = rcc.h hal.h spi.h uart.h LoRa.h exti.h

ifeq ($(OS),WINDOWS_NT)
	RM = cmd /C del /Q /F *.elf *~ *.o *.bin
else
	RM = rm -f *.bin *.elf *.o 
endif

build: firmware.elf firmware.bin

flash: firmware.bin
	st-flash --reset write $< 0x8000000

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

firmware.elf: $(SOURCES) $(HEADER)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

clean:
	$(RM)
