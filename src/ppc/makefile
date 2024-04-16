 #
 #	========================================================
 #
 #	CoreBoot
 # 	Date Added: 08/11/2023
 # 	Copyright 2024, Mahrouss Logic, all rights reserved.
 # 	
 # 	========================================================
 #

CC=ppc-elf-gcc
AS=ppc-elf-as
FIRMWARE=core-boot.elf
FLAGS=-c -mcpu=8540  -D__COMPILE_POWERPC__ -I../../ -Wall -c -nostdlib -ffreestanding -fno-builtin -D__BSTRICT__ -D__BDEBUG__
C_SRC=$(wildcard *.c) $(wildcard ../*.c) -c

AS_FLAGS= -c  -I../../ -c

LD=ppc-elf-ld
OBJ=$ $(wildcard *.o)
FLAGS_LD= --script=linkscript.ld -o $(FIRMWARE) -nostdlib

EMU=qemu-system-ppc64
EMU_FLAGS= -drive file=cdrom.epm,media=disk,snapshot=off,format=raw -device virtio-scsi-pci,id=scsi -smp 4 -device VGA -cpu e500 -d guest_errors,unimp -M ppce500 -bios $(FIRMWARE) -s


QEMU_IMG=qemu-img create -f qcow2 cdrom.epm 256M

# link (make firmware)
.PHONY: firmware-link
firmware-link: firmware-compile
	$(LD) $(OBJ) $(FLAGS_LD)
	$(QEMU_IMG)
	
# compile firmware
.PHONY: firmware-compile
firmware-compile:
	$(CC) $(FLAGS) $(C_SRC)
	$(AS) $(AS_FLAGS) ppc_boot.S -o ppc_boot.o

# launch qemu rule
.PHONY: run
run:
	$(EMU) $(EMU_FLAGS)

# launch qemu with attached debugger
.PHONY: run-dbg
run-dbg:
	$(EMU) $(EMU_FLAGS)

# remove object files
.PHONY: clean
clean:
	rm -f $(wildcard *.o) $(wildcard *.out)

.PHONY: all
all: firmware-link
	@echo "[CoreBoot] done."
