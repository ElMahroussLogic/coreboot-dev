[bits 16]

[org 0x7C00]

_start:
	jmp $

times 510 - ($-$$) nop

dw 0xaa55

;; Custom CoreBoot Bootable header

db "XPT", 0
;; build date
db "03/24/24", 0
;; Start code
dw 0x7c00
;; segment
dw 0xff00