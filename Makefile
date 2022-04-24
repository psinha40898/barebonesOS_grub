   OBJECTS = loader.o kernel/kmain.o drivers/screen.o drivers/io.o 
   C_SOURCES = $(wildcard kernel/*.c)
   HEADERS = $(wildcard kernel/*.h)
   OBJ = ${C_SOURCES:.c=.o} 

    CC = gcc
    CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
    LDFLAGS = -T link.ld -melf_i386
    AS = nasm
    ASFLAGS = -f elf

    all: kernel.elf

    kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

    os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
                    -b boot/grub/stage2_eltorito    \
                    -no-emul-boot                   \
                    -boot-load-size 4               \
                    -A os                           \
                    -input-charset utf8             \
                    -quiet                          \
                    -boot-info-table                \
                    -o /mnt/c/users/pyush/desktop/sp22/Bochs-2.7/os.iso                       \
                    iso

    kernel/kmain.o: kernel/kmain.c
	$(CC) $(CFLAGS)  $< -o $@

    drivers/screen.o: drivers/screen.c drivers/screen.h
	$(CC) $(CFLAGS)  $< -o $@

    drivers/io.o: drivers/io.s drivers/io.h 
	$(AS) $(ASFLAGS) $< -o $@

    %.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

    clean:
	rm -rf *.o kernel.elf os.iso

    
    
