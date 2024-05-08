; /********************************************************************************/
; /* NASM:  16-bit, org 0x0000                                                    */
; /* We do install the IVT by ourselves.                                          */
; /********************************************************************************/

[bits 16]
[org 0xf000]

%macro RomCall 1
    mov  sp, __ROM_LOOP_%1
    jmp  %1
__ROM_LOOP_%1:
%endmacro

;; Start ROM.
_StartLabel:
    cli
    cld

    mov ax, cs
    mov ds, ax
    mov ss, ax

    jmp _InitSuperIO
    jmp _StartLabel

_InitSuperIO:
    mov dx, 0x2e ; SuperIO chip base.

    in al, dx
    in al, dx

    mov si, _SuperIOConfiguration
    mov cx, (_SystemCOMTestString - _SuperIOConfiguration) / 2

_WriteSuperIOConf:
    mov ax, [si]
    RomCall _SerialOut
    add si, 0x02
    loop _WriteSuperIOConf

_InitSerial:
    mov si, _SuperIOConfigurationSerial
    mov cx, (_SystemCOMTestString - _SuperIOConfigurationSerial) / 2

_WriteSerialConf:
    mov ax, [si]
    RomCall _SuperIOOut
    add si, 0x02
    loop _WriteSerialConf

_SuperIOOut:
    mov dx, 0x3f8
    out  dx, al
    inc  dx
    xchg al, ah
    out  dx, al
    jmp  sp

_SerialOut:
    mov dx, 0x2e ; SUPER IO
    add dl, al
    mov al, ah
    out dx, al
    jmp sp

_PrintSplash:
    mov si, _SystemCOMTestString
    RomCall _PrintString

_EndLoop:
    jmp $

_PrintString:
    lodsb
    or al, al
    jnz _PrintChar
    jmp sp

_PrintChar:
    shl esp, 0x10
    RomCall _SerialPrintChar
    shr esp, 0x10
    jmp _PrintString

_SerialPrintChar:
    mov dx, 0x3f8 + 0x05
    mov ah, al
_TransmitWait:
    in al, dx
    and al, 0x20
    jz _TransmitWait
    mov dx, 0x3f8
    mov al, ah
    out dx, al
    jmp sp

_SuperIOConfiguration:
    db 0x0f ;; Enable COM, PAR and FDC.
    db 0x10 ;; LPT 378, COM1 3f8, COM2, 2f8
    db 0x00 ;; Clear COM1 test mode.

_SuperIOConfigurationSerial:
    db 0x00
    db 0x07
    db 0x80
    db 0x01
    db 0x00
    db 0x03

_SystemCOMTestString:
    db "NeWS AMD64 Firmware, (c) SoftwareLabs.", 0xa, 0xd, 0x0

_SystemDescriptorTable:
    dw 8               ; Length of table
    db 0xFC            ; IBM AT (same as F000:FFFE)
    db 0x01            ;        (same as F000:FFFF)
    db 0x04            ; BIOS revision level
    db 01100000b       ; Feature information
    dw 0

times 0xfff0-($-$$) nop ; pad up to fff0

jmp 0xF000:_StartLabel ; fff0: We start here after CPU reset

_SystemBiosDate: db "22/04/24", 0 ; fff5: BIOS release date

db 0xFC ; fffe: IBM AT
db 0x01 ; ffff: sub model id or something like that
