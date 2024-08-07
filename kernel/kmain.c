#include "../drivers/screen.h"
#include "../gdt/gdtload.h"
#include "../idt/isr.h"
#include "../drivers/keyboard.h"

#include <stdint.h>


int main(void)
{
	i686_GDT_Initialize();
	isr_install();
  clear_screen();
  // char *fb = (char *) 0x000B8000;
  // // fb[0] = 'N';
  // // fb[1] = 0x28;
  // move_cursor(90);
  asm volatile("sti");
  init_keyboard();



}
