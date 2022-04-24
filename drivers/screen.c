#include "screen.h"
#include "io.h"

#define fbCOMMAND_PORT  0x3D4
#define fbDATA_PORT 0x3D5



void set_cursor_offset(int offset);
void memory_copy(char *source, char *dest, int nbytes);


int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void kprint_test(char *message, int cursoroffset)
{
int row = get_offset_row(cursoroffset);
int col = get_offset_col(cursoroffset);

kprint_at(message, col, row);

}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
int print_char(char c, int col, int row, char attr);

/*INTERFACE*/
void kprint_at(char *message, int col, int row) {
    /* Set cursor if col/row are negative */
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    /* Loop through message and print it */
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLUE);
        /* Compute row/col for next iteration */
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void kprint(char *message) {
    kprint_at(message, -1, -1);
}

/*END*/
int print_char(char c, int col, int row, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLUE;

    /* Error control: print a red 'E' if the coords aren't right */
    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memory_copy((char*)get_offset(0, i) + VIDEO_ADDRESS,
                        (char*)get_offset(0, i-1) + VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = (char*)get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS;
        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}


void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}


int get_cursor_offset() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    outb(fbCOMMAND_PORT, 14);
    int offset = inb(fbDATA_PORT) << 8; /* High byte: << 8 */
    outb(fbCOMMAND_PORT, 15);
    offset += inb(fbDATA_PORT);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    outb(fbCOMMAND_PORT, 14);
    outb(fbDATA_PORT, (unsigned char)(offset >> 8));
    outb(fbCOMMAND_PORT, 15);
    outb(fbDATA_PORT, (unsigned char)(offset & 0xff));
}
void clear_screen()
{
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char *screen = (char *) 0x000B8000;
    for (i = 0; i < screen_size; i++)
    {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLUE;
    }
}

void move_cursor(unsigned short pos)
{
    outb(fbCOMMAND_PORT, 14);
    outb(fbDATA_PORT, ((pos >> 8) & 0x00FF));
    outb(fbCOMMAND_PORT, 15);
    outb(fbDATA_PORT, pos & 0x00FF);
}