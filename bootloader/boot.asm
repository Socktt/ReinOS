[org 0x7C00]

KERNEL_LOC equ 0x1000

mov [BOOT_DISK], dl         ; store boot disk from bios

mov bx, ok                  ; print it
call printStr               ; everything is fine?

mov dh, 18                  ; quite a bit of sectors

mov bx, 0
mov es, bx
mov bx, KERNEL_LOC
call readDisk               ; Read the Kernel, works perfectly

mov ah, 0x0
mov al, 0x13                ; 0x3 normal, 0x13 graphics
int 0x10                    ; clear screen

call enterPM

    jmp $

%include "./bootloader/readDisk.asm"
%include "./bootloader/printString.asm"
%include "./bootloader/printDec.asm"
%include "./bootloader/gdt.asm"

%include "./bootloader/EnterPM.asm"



ok: db "OK", 10, 13, 0

[bits 32]

BEGIN_PM:
    ;mov [0xb8000], dword 0x1F4B1F4F
    jmp KERNEL_LOC
    ; If anything happens we fecked up
    mov [0xb8002], dword 0x1F4F1F4B
    jmp $
times 510-($-$$) db 0
db 0x55, 0xAA
