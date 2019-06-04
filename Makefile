SRC = src
INCLUDE = include
LOG = log
OBJ = obj
BUILD = build
OUT = iso
CONF = conf
NAME = hpOS

CC = clang
CCOPTS = -I$(INCLUDE) -std=c11 -ffreestanding -fno-rtti -fno-exceptions -m32 -fwritable-strings -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nodefaultlibs -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable -c

ASM_SOURCES = $(shell find $(src) -name '*.s')
ASM_OBJECTS = $(patsubst ./$(SRC)/%.s,./$(OBJ)/%.s.o,$(ASM_SOURCES))

C_SOURCES = $(shell find $(src) -name '*.c')
C_OBJECTS = $(patsubst ./$(SRC)/%.c,./$(OBJ)/%.c.o,$(C_SOURCES))

.PHONY = all run dirs clean

all: run

run: $(OUT)/$(NAME).iso
	bochs -f $(CONF)/bochs.txt -q

clean:
	rm -rf log/* obj/* build/* iso/*

dirs: 
	mkdir -p $(OUT)/boot/grub

$(OBJ)/%.s.o: $(SRC)/%.s
	nasm -f elf32 $< -o $@
	
$(OBJ)/%.c.o: $(SRC)/%.c
	$(CC) $(CCOPTS) $< -o $@

$(BUILD)/kernel.elf: $(C_OBJECTS) $(ASM_OBJECTS)
	ld -T $(CONF)/link.ld -melf_i386 $^ -o $(BUILD)/kernel.elf
	
$(OUT)/$(NAME).iso: dirs $(BUILD)/kernel.elf
	cp -f $(BUILD)/kernel.elf $(OUT)/boot
	cp -f $(CONF)/grub.cfg $(OUT)/boot/grub
	grub-mkrescue -o $@ $(OUT)
	