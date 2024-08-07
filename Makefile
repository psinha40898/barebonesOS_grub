   OBJECTS = loader.o kernel/kmain.o drivers/screen.o drivers/io.o util/tools.o gdt/gdtload.o gdt/gdt.o idt/idtload.o idt/idt.o idt/isrload.o idt/isr.o drivers/keyboard.o
   C_SOURCES = $(wildcard kernel/*.c)
   HEADERS = $(wildcard kernel/*.h)
   OBJ = ${C_SOURCES:.c=.o} 

    CC = gcc
    CFLAGS = -m32 -fno-builtin -fno-stack-protector \
             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
    LDFLAGS = -T link.ld -melf_i386
    AS = nasm
    ASFLAGS = -f elf

    all: kernel.elf

    kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

    oshome.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
                    -b boot/grub/stage2_eltorito    \
                    -no-emul-boot                   \
                    -boot-load-size 4               \
                    -A os                           \
                    -input-charset utf8             \
                    -quiet                          \
                    -boot-info-table                \
                    -o os.iso                       \
                    iso
                    

    kernel/kmain.o: kernel/kmain.c
	$(CC) $(CFLAGS)  $< -o $@
	
    drivers/keyboard.o: drivers/keyboard.c drivers/keyboard.h 
	$(CC) $(CFLAGS)  $< -o $@
	
    idt/isr.o: idt/isr.c idt/isr.h 
	$(CC) $(CFLAGS)  $< -o $@
	
    idt/isrload.o: idt/isr.s idt/isr.h 
	$(AS) $(ASFLAGS) $< -o $@
		
    idt/idt.o: idt/idt.c idt/idtload.h 
	$(CC) $(CFLAGS)  $< -o $@
	
    idt/idtload.o: idt/idtload.s idt/idtload.h 
	$(AS) $(ASFLAGS) $< -o $@
		
    gdt/gdt.o: gdt/gdt.c gdt/gdtload.h 
	$(CC) $(CFLAGS)  $< -o $@
	
    gdt/gdtload.o: gdt/gdtload.s gdt/gdtload.h 
	$(AS) $(ASFLAGS) $< -o $@
	
    util/tools.o: util/tools.c util/tools.h
	$(CC) $(CFLAGS)  $< -o $@
		
    drivers/screen.o: drivers/screen.c drivers/screen.h
	$(CC) $(CFLAGS)  $< -o $@

    drivers/io.o: drivers/io.s drivers/io.h 
	$(AS) $(ASFLAGS) $< -o $@
		
    %.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

    clean:
	rm -rf *.o kernel.elf os.iso

    
    
