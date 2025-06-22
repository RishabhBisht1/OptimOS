#include <stdint.h>
#include "io.h"
#include "keyboard.h"
#include "shell.h"
#include "screen.h"

//#define VIDEO_MEMORY 0xB8000
//#define WHITE_ON_BLACK 0x0F

/*uint16_t* video = (uint16_t*) VIDEO_MEMORY;
static int cursor = 0;

void print(const char* str) {
    while (*str) {
        video[cursor++] = (*str++ | (WHITE_ON_BLACK << 8));
    }
}

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++)
        video[i] = ' ' | (WHITE_ON_BLACK << 8);
    cursor = 0;
}*/

void kernel_main() {
    clear_screen();
    print("Welcome to MiniOS CLI\n\n");
    start_shell();
    for (;;) { __asm__("hlt"); }
}

/*char map_scancode_to_ascii(uint8_t scancode) {
    const char* kbd = "??1234567890-=??qwertyuiop[]??asdfghjkl;'`??zxcvbnm,./?? ";
    if (scancode > 0 && scancode < 58)
        return kbd[scancode];
    return 0;
}*/

