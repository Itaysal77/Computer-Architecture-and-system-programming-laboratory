section	.rodata			
	intF: dd `%d  \n`,10 ,0
section .text
global assFunc
extern c_checkValidity
extern printf

assFunc:                        
    push ebp              		; save Base Pointer (bp) original value
    mov ebp, esp         		; use Base Pointer to access stack contents (do_Str(...) activation frame)
    pushad                   	; push all signficant registers onto stack (backup registers values)
    mov ecx, dword [ebp+8]	    ;arg int x
    push dword ecx
    call c_checkValidity
    add esp,4                   ;“free" space allocated for function arguments in Stack
    cmp eax,0x31                ;compare to 1
    jne is_zero
    shl ecx,2                   ;*4
    jmp forword                 ;skip is_zero
is_zero:
    shl ecx,3                   ;*8
    jmp forword
forword:
    push ecx                    ;argument for printf(the output number)
    push intF                   ;aargument for the print format of int
    call printf
    add esp,8                   ; “free" space allocated for function arguments in Stack
    popad                    	; restore all previously used registers
    mov esp, ebp			; free function activation frame
    pop ebp				; restore Base Pointer previous value (to returnt to the activation frame of main(...))
    ret			
