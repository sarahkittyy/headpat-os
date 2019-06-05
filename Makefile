SRC = src
INCLUDE = include
LOG = log
OBJ = obj
BUILD = build
OUT = iso
CONF = conf
NAME = hpOS

CC = clang
CCOPTS = -I$(INCLUDE) -std=gnu99 -ffreestanding -fno-rtti -fno-exceptions -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nodefaultlibs -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable -c

ASM_SOURCES = $(SRC)/loader.s $(shell find $(SRC) ! -name 'loader.s' -name '*.s' -type f)
ASM_OBJECTS = $(patsubst $(SRC)/%.s,$(OBJ)/%.s.o,$(ASM_SOURCES))

$(info $(ASM_OBJECTS))

C_SOURCES = $(shell find $(SRC) -name '*.c')
C_OBJECTS = $(patsubst $(SRC)/%.c,$(OBJ)/%.c.o,$(C_SOURCES))

.PHONY = all run dirs clean

all: run

run: $(OUT)/$(NAME).iso
	bochs -f $(CONF)/bochs.txt -q || true

clean:
	rm -rf log/* obj/* build/* iso/*

dirs: 
	mkdir -p $(OUT)/boot/grub
	rsync -av --include='*/' --exclude='*' $(INCLUDE)/ $(OBJ)/

$(OBJ)/%.s.o: $(SRC)/%.s dirs
	nasm -f elf32 $< -o $@
	
$(OBJ)/%.c.o: $(SRC)/%.c dirs
	$(CC) $(CCOPTS) $< -o $@

$(BUILD)/kernel.elf: $(ASM_OBJECTS) $(C_OBJECTS)
	ld --build-id=none -T $(CONF)/link.ld -melf_i386 $^ -o $(BUILD)/kernel.elf
	if grub-file --is-x86-multiboot $(BUILD)/kernel.elf; then \
		echo MULTIBOOT_CONFIRMED; \
		true; \
	else \
		echo MULTIBOOT_NOT_CONFIRMED; \
		false; \
	fi;
	
$(OUT)/$(NAME).iso: dirs $(BUILD)/kernel.elf
	cp -f $(BUILD)/kernel.elf $(OUT)/boot
	cp -f $(CONF)/grub.cfg $(OUT)/boot/grub
	grub-mkrescue -o $@ $(OUT)
	