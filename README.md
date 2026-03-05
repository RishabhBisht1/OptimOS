# OptimOS
Overview

OptimOS is a simple educational operating system built from scratch using C and x86 Assembly. The project demonstrates fundamental OS concepts such as bootloading, kernel initialization, hardware interaction, and a basic command-line shell.

The main goal of this project is to understand how an operating system boots and interacts with hardware without relying on existing operating systems.

## Features

Custom Bootloader
- Written in x86 Assembly
- Loads the kernel from disk into memory
- Transfers control to the kernel

## Basic Kernel
  - Written primarily in C
  - Initializes system components
  - Handles screen output

## Keyboard Driver
 - Reads keyboard input from hardware ports
 - Converts scancodes into characters
  
## Screen Driver
  - Writes directly to the VGA text buffer
  - Displays text on the screen

## Simple Command Shell
  - Accepts user input
  - Executes basic commands

## Requirements

- To build and run this OS you need:
- GCC
- NASM
- LD (linker)
- Make
- QEMU

## Future Improvements
Possible extensions include:

- Memory management

- File system support (FAT12/FAT16)

- Interrupt handling

- Multitasking

- More advanced shell commands
