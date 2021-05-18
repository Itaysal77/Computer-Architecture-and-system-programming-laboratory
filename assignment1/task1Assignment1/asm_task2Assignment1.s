section	.rodata			; we define (global) read-only variables in .rodata section
	format_string: db "%s", 10, 0	; format string

section .bss			; we define (global) uninitialized variables in .bss section
	an: resb 12		; enough to store integer in [-2,147,483,648 (-2^31) : 2,147,483,647 (2^31-1)]

section .data
	len: dd 0

section .text
	global convertor
	extern printf

convertor:
	push ebp
	mov ebp, esp	
	pushad			

	mov ecx, dword [ebp+8]	; get function argument (pointer to string)

	; your code comes here...
	mov ebx, an

	loop:
		mov al, [ecx]	; work with pointer to char al register
		cmp al, 113		; comparing to q ASCII
		je endProgram
		cmp al, 0		; check if we finished the string and end with a print
		je end
		cmp al, 10		;check if '/n', if yes, move to next char
		je nextChar
		sub al, 48		; sub from all 48
		cmp al, 17		;checks if A-F
		jl number
		sub al, 7		;if yes sub 7 more
	number:
		cmp al,8		;check if bigger then 8(the last bit is 1 if it is bigger)
		jl less8		; func for putting 0 in the first place and continue the check
		mov byte[ebx], 0x31	;add 1 to first place
		sub al, 8		;now we will check x-8 value for next byte
	next_digit_1:		; same check for second digit in char
		inc ebx			;inc the ebx pointer for next digit
		cmp al, 4
		jl less4
		mov byte[ebx], 0x31
		sub al, 4
	next_digit_2:		;check for third binary digit
		inc ebx
		cmp al, 2
		jl less2
		mov byte[ebx], 0x31
		sub al, 2
	next_digit_3:		;check for fourth binary digit
		inc ebx
		cmp al, 1
		jl less1
		mov byte[ebx], 0x31
		sub al, 1
		inc ebx		;for next char, inc ebx here as well 
		jmp nextChar	

	less8:			;func for 0 in first binary digit and continue
		mov byte[ebx], 0x30
		jmp next_digit_1
	less4:
		mov byte[ebx], 0x30
		jmp next_digit_2
	less2:
		mov byte[ebx], 0x30
		jmp next_digit_3
	less1:
		mov byte[ebx], 0x30
		inc ebx
	nextChar:		;next char in string
		inc ecx		;promoting the arg string
		jmp loop	; cotinue loop with new char ecx pointer
	end:
	    mov byte[ebx],0
		push an			; call printf with 2 arguments -  
		push format_string	; pointer to str and pointer to format string
		call printf
		add esp, 8		; clean up stack after call
		popad			
		mov esp, ebp	
		pop ebp
		mov eax, 1		; return 1 for c program flag to keep getting string
		ret
	endProgram:		;if we got 'q' char by arg, return 0 for exit
		popad			
		mov esp, ebp	
		pop ebp
		mov eax, 0
		ret

