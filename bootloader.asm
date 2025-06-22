[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Load 15 sectors of kernel starting from sector 2 to 0x10000 (physical)
    mov bx, 0x0000       ; offset in ES
    mov ax, 0x1000       ; segment that maps to phys 0x10000
    mov es, ax           ; ES = 0x1000

    mov ah, 0x02         ; read sectors
    mov al, 15           ; number of sectors
    mov ch, 0            ; cylinder
    mov cl, 2            ; sector 2 (sector 1 is bootloader)
    mov dh, 0            ; head
    mov dl, 0x80         ; first hard disk
    int 0x13

    ; Enable A20 line (basic method)
    in al, 0x92
    or al, 0x02
    out 0x92, al

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Enter protected mode
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_pm

; GDT: 3 entries, each 8 bytes
gdt_start:
    dq 0x0000000000000000   ; Null descriptor
    dq 0x00CF9A000000FFFF   ; Code segment descriptor
    dq 0x00CF92000000FFFF   ; Data segment descriptor
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

[BITS 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000       ; Stack pointer

    ; Far jump to kernel at physical 0x10000 (segment 0x1000:0)
    jmp 0x08:0x10000

times 510-($-$$) db 0
db 0x55
db 0xAA

