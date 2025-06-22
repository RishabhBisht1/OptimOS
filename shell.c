#include <stdint.h>
#include "io.h"           // for inb(), outb()
#include "keyboard.h"     // map_scancode_to_ascii
#include "screen.h"       // print(), clear_screen()

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

// Simple strcmp implementation (no stdlib)
static int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// Simple strncmp implementation
static int strncmp(const char* s1, const char* s2, int n) {
    for (int i = 0; i < n && s1[i] && s1[i] == s2[i]; i++) {}
    if (n == 0) return 0;
    return (unsigned char)s1[0] - (unsigned char)s2[0];
}

void read_input(char* buffer) {
    int index = 0;
    while (1) {
        // Wait for a scancode
        while (!(inb(KEYBOARD_STATUS_PORT) & 1)) {}
        uint8_t scancode = inb(KEYBOARD_DATA_PORT);

        // Enter key
        if (scancode == 0x1C) {
            buffer[index] = '\0';
            print("\n");
            return;
        }
        // Backspace
        else if (scancode == 0x0E && index > 0) {
            index--;
            print("\b \b");
        }
        // Key press (no release)
        else if (!(scancode & 0x80)) {
            char c = map_scancode_to_ascii(scancode & 0x7F);
            if (c) {
                buffer[index++] = c;
                char s[2] = {c, '\0'};
                print(s);
            }
        }
    }
}

void start_shell() {
    char input[128];
    while (1) {
        print("\n> ");
        read_input(input);

        if (strcmp(input, "help") == 0) {
            print("Commands:\n");
            print("help - list commands\n");
            print("clear - clear screen\n");
            print("echo - repeat text\n");
            print("info - OS info\n");
        } else if (strcmp(input, "clear") == 0) {
            clear_screen();
        } else if (strncmp(input, "echo ", 5) == 0) {
            print(input + 5);
        } else if (strcmp(input, "info") == 0) {
            print("MiniOS v0.1 by OptiML LLC\n");
            print("A simple x86 protected mode CLI shell\n");
        } else {
            print("Unknown command");
        }
    }
}

