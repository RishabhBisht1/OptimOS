// screen.c (updated)
#include <stdint.h>
#include "screen.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_COLS 80
#define MAX_ROWS 25
#define WHITE_ON_BLACK 0x0F

static int cursor_row = 0;
static int cursor_col = 0;

// Move the cursor to (row, col)
static void move_cursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
}

// Scroll up by one line
static void scroll_if_needed() {
    if (cursor_row < MAX_ROWS) return;

    // Copy lines 1..24 up to 0..23
    uint16_t* video = (uint16_t*)VIDEO_ADDRESS;
    for (int r = 1; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            video[(r-1)*MAX_COLS + c] = video[r*MAX_COLS + c];
        }
    }
    // Clear last line
    for (int c = 0; c < MAX_COLS; c++) {
        video[(MAX_ROWS-1)*MAX_COLS + c] = ' ' | (WHITE_ON_BLACK << 8);
    }
    cursor_row = MAX_ROWS - 1;
}

// Print a null-terminated string, handling '\n' and '\b'
void print(const char* str) {
    uint16_t* video = (uint16_t*)VIDEO_ADDRESS;
    while (*str) {
        char ch = *str++;
        if (ch == '\n') {
            cursor_col = 0;
            cursor_row++;
        } else if (ch == '\b') {
            if (cursor_col > 0) {
                cursor_col--;
            } else if (cursor_row > 0) {
                cursor_row--;
                cursor_col = MAX_COLS - 1;
            }
            video[cursor_row*MAX_COLS + cursor_col] = ' ' | (WHITE_ON_BLACK << 8);
        } else {
            video[cursor_row*MAX_COLS + cursor_col] = ch | (WHITE_ON_BLACK << 8);
            cursor_col++;
            if (cursor_col >= MAX_COLS) {
                cursor_col = 0;
                cursor_row++;
            }
        }
        scroll_if_needed();
    }
}

// Clear screen and reset cursor
void clear_screen(void) {
    uint16_t* video = (uint16_t*)VIDEO_ADDRESS;
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        video[i] = ' ' | (WHITE_ON_BLACK << 8);
    }
    move_cursor(0, 0);
}

