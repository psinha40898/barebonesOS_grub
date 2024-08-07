
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLUE 0x1f
#define RED_ON_WHITE 0xf4
#define VIDEO_ADDRESS 0xb8000

void clear_screen();
void kdelete_char();
void kmove_down();
void move_cursor(unsigned short pos);
void kprint_at(char *message, int col, int row);
void kprint(char *message);
void kprint_test(char *message, int cursoroffset);







int get_cursor_offset();



