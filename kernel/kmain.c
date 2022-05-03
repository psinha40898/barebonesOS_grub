#include "../drivers/screen.h"
#include "../drivers/io.h"
#include "../gdt/gdtload.h"
#include "../idt/idtload.h"
#include "../idt/isr.h"

#include <stdint.h>


int main(void)
{
	i686_GDT_Initialize();
	isr_install();

clear_screen();
char *fb = (char *) 0x000B8000;
fb[0] = 'N';
fb[1] = 0x28;
move_cursor(90);
  
   __asm__ __volatile__("int $2");
   __asm__ __volatile__("int $3");
  

kprint("TEST3");



/* nice job 

get the external function working in gdt.c then we good
*/ 





}
