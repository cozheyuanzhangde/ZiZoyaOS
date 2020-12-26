clear_screen_16bit:                ; function for clear pre-load info including BIOS info  
    mov    ah, 0x06                ; Write #0x06 instruction for int 0x10 
    mov    al, 0 
    mov    ch, 0
    mov    ch, 0    
    mov    dh, 24 
    mov    dl, 79
    mov    bh, 0x07  
    int 0x10                       ; call BIOS function 0x10 to print char in al
    ret