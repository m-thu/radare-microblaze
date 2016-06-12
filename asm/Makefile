# MicroBlaze toolchain (little endian)
TARGET=microblazeel-elf
PREFIX=~/$(TARGET)

CC=$(PREFIX)/bin/$(TARGET)-gcc
AS=$(PREFIX)/bin/$(TARGET)-as
OBJCOPY=$(PREFIX)/bin/$(TARGET)-objcopy

test.bin: test.o
	$(OBJCOPY) -O binary test.o test.bin

test.o: test.s
	$(AS) -o test.o test.s

clean:
	rm -f *.o

.PHONY: clean
