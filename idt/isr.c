#include "isr.h"
#include "idtload.h"
#include "../drivers/screen.h"
#include "../drivers/io.h"
#include "../util/tools.h"
isr_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
    IDT_SetGATE(0, isr0);
    IDT_SetGATE(1, isr1);
    IDT_SetGATE(2, isr2);
    IDT_SetGATE(3, isr3);
    IDT_SetGATE(4, isr4);
    IDT_SetGATE(5, isr5);
    IDT_SetGATE(6, isr6);
    IDT_SetGATE(7, isr7);
    IDT_SetGATE(8, isr8);
    IDT_SetGATE(9, isr9);
    IDT_SetGATE(10, isr10);
    IDT_SetGATE(11, isr11);
    IDT_SetGATE(12, isr12);
    IDT_SetGATE(13, isr13);
    IDT_SetGATE(14, isr14);
    IDT_SetGATE(15, isr15);
    IDT_SetGATE(16, isr16);
    IDT_SetGATE(17, isr17);
    IDT_SetGATE(18, isr18);
    IDT_SetGATE(19, isr19);
    IDT_SetGATE(20, isr20);
    IDT_SetGATE(21, isr21);
    IDT_SetGATE(22, isr22);
    IDT_SetGATE(23, isr23);
    IDT_SetGATE(24, isr24);
    IDT_SetGATE(25, isr25);
    IDT_SetGATE(26, isr26);
    IDT_SetGATE(27, isr27);
    IDT_SetGATE(28, isr28);
    IDT_SetGATE(29, isr29);
    IDT_SetGATE(30, isr30);
    IDT_SetGATE(31, isr31);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0); 
    IDT_SetGATE(32, irq0);
    IDT_SetGATE(33, irq1);
    IDT_SetGATE(34, irq2);
    IDT_SetGATE(35, irq3);
    IDT_SetGATE(36, irq4);
    IDT_SetGATE(37, irq5);
    IDT_SetGATE(38, irq6);
    IDT_SetGATE(39, irq7);
    IDT_SetGATE(40, irq8);
    IDT_SetGATE(41, irq9);
    IDT_SetGATE(42, irq10);
    IDT_SetGATE(43, irq11);
    IDT_SetGATE(44, irq12);
    IDT_SetGATE(45, irq13);
    IDT_SetGATE(46, irq14);
    IDT_SetGATE(47, irq15);
    i686_IDT_Initialize(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]);
    kprint("\n");
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) outb(0xA0, 0x20); /* slave */
    outb(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}