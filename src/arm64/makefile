 #
 #	========================================================
 #
 #	CoreBoot
 # 	Date Added: 08/11/2023
 # 	Copyright 2024, SoftwareLabs, all rights reserved.
 #
 # 	========================================================
 #

CC=arm-none-eabi-gcc-13.2.1
AS=arm-none-eabi-as

FIRMWARE=firmware.rom

FLAGS=-c -D__COMPILE_ARM64__ -I../../ -Wall -c -nostdlib -ffreestanding -fno-builtin \
		-D__BSTRICT__ -D__BDEBUG__

C_SRC=$(wildcard *.c) $(wildcard ../*.c) -c

AS_FLAGS= -c -I../../

LD=arm-none-eabi-ld
OBJ=*.o
FLAGS_LD= --script=linkscript.ld -o core-boot.elf -nostdlib

EMU=qemu-system-arm
EMU_FLAGS=-M vexpress-a15 -cpu cortex-a15 -kernel $(FIRMWARE) -s

WAIT=sleep 1

IMG_CMD=qemu-img create -f qcow2 epm.img 256M

.PHONY: all
all: firmware-link
	@echo "[CoreBoot] build done."

.PHONY: firmware-link
firmware-link: firmware-compile
	$(LD) $(OBJ) $(FLAGS_LD)

.PHONY: make-rom
make-rom:
	$(IMG_CMD)
	qemu-img create -f raw firmware.rom 512K
	dd if=core-boot.elf of=firmware.rom bs=1 seek=0 conv=notrunc

# compile firmware
.PHONY: firmware-compile
firmware-compile:
	$(CC) $(FLAGS) $(C_SRC)
	$(AS) -march=armv7-a -mcpu=cortex-a15 arm64-start-context.S -o arm64-start-context.o
	$(AS) -march=armv7-a -mcpu=cortex-a15 arm64-boot.S -o arm64-boot.o
	

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
	rm -f $(wildcard *.o) $(wildcard *.elf) $(wildcard *.rom) $(wildcard *.epm)
