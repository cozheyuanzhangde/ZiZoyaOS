[bits 16]
switch_to_pm:
    cli                   ; switch off interrupts
    lgdt [gdt_descriptor] ; load gdt descriptor
    mov eax, cr0          ; start switching to protected mode: store cr0 in eax
    or eax, 0x1           ; do OR operation to eax with 0x1 to set first bit(AND exclude certain bit, OR include certain bit)
    mov cr0, eax          ; store eax in cr0, make the switch
    jmp CODE_SEG:init_pm  ; far jump tp new segment

[bits 32]
init_pm:
    mov ax, DATA_SEG      ; point old segment registers to DATA_SEG in gdt
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000      ; update stack position to 0x90000
    mov esp, ebp

    call BEGIN_PM         ;