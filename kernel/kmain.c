#include "../drivers/screen.h"
#include "../drivers/io.h"
#include "../gdt/gdtload.h"
#include <stdint.h>


int main(void)
{
	i686_GDT_Initialize();

clear_screen();
char *fb = (char *) 0x000B8000;
fb[0] = 'N';
fb[1] = 0x28;
move_cursor(90);


kprint("TEST3");



/* nice job 

get the external function working in gdt.c then we good
*/ 





}
