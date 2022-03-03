CROSS_PATH=$(HOME)/opt/cross/bin

LD=$(CROSS_PATH)/i686-elf-ld
CC=$(CROSS_PATH)/i686-elf-gcc

ASM=nasm
ECHO=echo -e
QEMU=qemu-system-i386
GDB=gdb

CFLAGS=-g -ffreestanding -falign-jumps -falign-functions -falign-labels \
	-falign-loops -fstrength-reduce -fomit-frame-pointer \
	-finline-functions -Wno-unused-function -fno-builtin -Werror \
	-Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib \
	-nostartfiles -nodefaultlibs -Wall -O0
INCLUDES=-I.

NO_SECTORS=100

OBJS=build/kernel.asm.o build/kernel.o build/idt/idt.asm.o build/idt/idt.o \
	build/mm/mem.o build/io/io.asm.o build/string/string.o

# VESA Driver
OBJS+=build/drivers/vesa/vesa.o build/drivers/vesa/terminal.o \
	build/drivers/vesa/fonts/vga.o

all: build/boot/boot.bin build/kernel.out
	@dd if=build/boot/boot.bin > kinl.bin
	@dd if=build/kernel.out >> kinl.bin
	@dd if=/dev/zero bs=512 count=$(NO_SECTORS) >> kinl.bin

build/kernel.out: $(OBJS)
	@$(LD) -g -relocatable $(OBJS) -o build/kernelfull.o
	@$(CC) $(CFLAGS) -T linker.ld -o $@ -ffreestanding -O0 -nostdlib \
		build/kernelfull.o

build/boot/boot.bin: boot/bios.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) -f bin $< -o $@

build/kernel.asm.o: sys/kernel.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) -f elf -g $< -o $@

build/kernel.o: sys/kernel.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

build/idt/idt.asm.o: sys/idt/idt.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) -f elf -g $< -o $@

build/idt/idt.o: sys/idt/idt.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

build/mm/mem.o: sys/mm/mem.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

build/io/io.asm.o: sys/io/io.asm
	@$(ECHO) "ASM\t\t"$<
	@$(ASM) -f elf -g $< -o $@

build/string/string.o: sys/string/string.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

# VESA Driver
build/drivers/vesa/vesa.o: drivers/vesa/vesa.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

build/drivers/vesa/terminal.o: drivers/vesa/terminal.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

build/drivers/vesa/fonts/vga.o: drivers/vesa/fonts/vga.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $(INCLUDES) -std=gnu99 -c $< -o $@

gdb: all
	@$(GDB) -ex "set confirm off" \
			-ex "add-symbol-file build/kernelfull.o 0x0100000" \
			-ex "target remote | qemu-system-i386 -hda kinl.bin -S -gdb stdio"

run: all
	@$(QEMU) -hda kinl.bin

clean:
	@rm -Rf build/boot/boot.bin build/kernel.out \
		build/kernelfull.o $(OBJS)
