# ===============================
# CoreBoot amd64 backend, 'CoreBoot'
# (C) VICTOR Electronics Corp
# Runtime 0 makefile.
# ===============================

ASM				= nasm
ROM				= romboot.rom
ROM_SOURCE		= romboot.asm
BOOT_TEST_SOURCE = testboot-xpt.asm
BOOT_TEST		= testboot-xpt.rom
BOOT			= romboot-xpt.rom
BOOT_SOURCE		= romboot-xpt.asm
EMU				= qemu-system-x86_64

.PHONY: all
all: compile-xpm-test compile-rom compile-xpm-rom

.PHONY: clean-output
clean-output:
	rm $(ROM) $(BOOT) $(BOOT_TEST)

.PHONY: compile-xpm-test
compile-xpm-test:
	$(ASM) -f bin $(BOOT_TEST_SOURCE) -o $(BOOT_TEST)

.PHONY: compile-rom
compile-rom:
	$(ASM) -f bin $(ROM_SOURCE) -o $(ROM)

.PHONY: compile-xpm-rom
compile-xpm-rom:
	$(ASM) -f bin $(BOOT_SOURCE) -o $(BOOT)

.PHONY: run-test-xpm
run-test-xpm:
	$(EMU) -M q35 -fda $(BOOT) -hda $(BOOT_TEST) -d int

.PHONY: run-rom
run-rom:
	$(EMU) -M q35 -bios $(ROM) -d cpu_reset
