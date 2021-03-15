                        ; BX is pointer to text

printStr:
    pusha
    mov ah, 0x0E        ; you should know this

    print_loop:
        mov al, [bx]    ; TA FETE BABABABABABAABAAAAAA BABABABABAAAAAAAAAAAAA
        cmp al, 0
        jne disp_char
        popa
        ret

    disp_char:
        int 0x10
        add bx, 1
        jmp print_loop
        