#pragma once

#include <stdint.h>

// Print a null‑terminated string to the VGA text buffer
void print(const char* str);

// Clear the VGA text buffer and reset cursor
void clear_screen(void);

