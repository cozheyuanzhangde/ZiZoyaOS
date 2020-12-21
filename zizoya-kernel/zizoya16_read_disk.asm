disk_load_16bit:
    push dx              ; record the number of sectors to be read
    mov ah, 0x02         ; Write #0x02 instruction for int 0x13
    mov al, dh           
    mov ch, 0x00         ; cylinder 0
    mov dh, 0x00         ; head 0
    mov cl, 0x02         ; read the second sector
    int 0x13             ; call BIOS function 0x13 to read sectors
    jc disk_read_error   ; jump if carry set -> disk_error
    pop dx               
    cmp dh, al           ; compare dh and al
    jne disk_read_error  ; jump if not equal -> disk_error
    ret

disk_read_error:              ;print disk read error message
    mov si, ERROR_Message
    call print_string_16bit
    jmp $


ERROR_Message db 'Failed to read disk as expected!', 0 ;define/declare bytes for ERROR_Message, use 0 as null terminator
