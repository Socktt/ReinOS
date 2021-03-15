                    ; DH is sector count
                    ; ES:BX is where to load in mem

readDisk:
    mov ah, 0x02    ; Read disk
    mov al, dh

    xor dx, dx

    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    mov dl, [BOOT_DISK]
    int 0x13

    jc retry
    cmp ah, 0
    jne retry
    mov bx, ax
    call PrintDecimal
    ret

retry:
    mov bx, ax
    call PrintDecimal
    jmp readDisk

diskErr:
    pusha
    mov bx, DISK_ERR_MSG
    call printStr
    popa
    xor bx, bx
    mov bl, ah
    call PrintDecimal
    jmp $

DISK_ERR_MSG: db "Disk Error! :(", 10, 13, 0
BOOT_DISK: db 0     ; Placeholder