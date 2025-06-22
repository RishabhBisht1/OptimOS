CROSS=
CC=$(CROSS)gcc
LD=$(CROSS)ld
AS=nasm

CFLAGS=-m32 -ffreestanding -O0 -Wall -Wextra
LDFLAGS=-m elf_i386
OBJS = start.o kernel.o screen.o shell.o keyboard.o

all: os_image.bin

bootloader.bin: bootloader.asm
	$(AS) -f bin bootloader.asm -o bootloader.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) -f elf32 $< -o $@

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel.elf $(OBJS)

kernel.bin: kernel.elf
	objcopy -O binary kernel.elf kernel.bin

os_image.bin: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > os_image.bin
	truncate -s 1M os_image.bin

clean:
	rm -f *.bin *.o *.elf *.img os_image.bin

