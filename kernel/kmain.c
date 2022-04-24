#include "../drivers/screen.h"
#include "../drivers/io.h"



int main(void)
{
clear_screen();
char *fb = (char *) 0x000B8000;
fb[0] = 'N';
fb[1] = 0x28;
move_cursor(90);

kprint("TEST");


/* nice job */ 





}
