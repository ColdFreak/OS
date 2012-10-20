[BITS 32]
global start
start:
    mov esp, _sys_stack ; This points the stack to our new stack area
    jmp stublet

; This part MUST be 4byte aligned, so we solve that issue using 'ALIGN 4'
mboot:
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_PAGE_ALIGN    equ 1<<0
    MULTIBOOT_MEMORY_INFO   equ 1<<1
    MULTIBOOT_AOUT_KLUDGE   equ 1<<16
    MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002
    MULTIBOOT_HEADERFLAGS   equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM      equ -(MULTIBOOT_HEADER_MAGIC+MULTIBOOT_HEADERFLAGS)
    EXTERN code, bss, end

    ; This is the GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADERFLAGS
    dd MULTIBOOT_CHECKSUM

    ; AOUT kludge - must be physical addresses. make a note of these:
    ; The linker script filess in the data for these ones
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; This is and endless loop here. Make a note of this: Later on, we will
; insert an 'exter _main' followed by 'call _main', right
; before the 'jmp $'.
stublet:
    extern _main	; The compiler gcc will put an underscore in front of all of the function and variable names when it compiles.
					; Therefore, to reference a function or variable from our assembly code, we must add an underscore to the function name
					; if the function is in a C source file!!!
    call _main
    jmp $


; Shortly we will add code for loading the GDT right here!
; This will set up our new sgement register. We need to do 
; something special in order to se CS. We do what is called
; a far jump. A jump that includes a sgement as well as an 
; offset.
; This is declared in C as ' extern void gdt_flush()'

global _gdt_flush
extern _gp

_gdt_flush:
	lgdt [_gp] ; Load the GDT with our '_gp' which is a special pointer
	mov ax, 0x10 ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2 ; 0x08 is the offset to our code sgement: Far jump!
flush2:
	ret	; Returns back to the C code!

; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines(ISRs) right here!


; Here is the definition of our BSS section. Right now, we'll use
; it just to store the stack. Remember that a stack actually grows
; downwards, so we declare the size of the data before declaring
; the identifier '_sys_stack'
SECTION .bss
    resb 8192   ; This reserves 8K bytes of memory here
_sys_stack:


