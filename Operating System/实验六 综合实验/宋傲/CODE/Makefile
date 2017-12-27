#!Makefile

#Get pathes of sources and objects
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(C_SOURCES:.c=.o)
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(S_SOURCES:.s=.o)

#Alias
CC = gcc
LD = ld
ASM = nasm

# -Wall: show all warning info
# -m32: cross compiling to 32 bit
# -ggdb: compile with debug info
# -gstabs+: produce debugging information in stabs format
# -nostdinc: ignores standard C include directories
# -fno-builtin: Don’t recognize built-in functions that do not begin with ‘__builtin_’ as prefix.
# -fno-stack-protector: disable stack protector
# -I include: include path is ./include
C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include

# -T read link commands from a file
# -m elf_i386: link for elf_i386 platform
# -nostdlib: link without standard library
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -nostdlib

# -f: Specifying the Output File Format
# -F: Selecting a Debug Information Format 
ASM_FLAGS = -f elf -g -F stabs

all: clean  $(S_OBJECTS) $(C_OBJECTS) link update_image

%.o : %.s
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $< 

%.o : %.c
	@echo 编译代码文件 $< ...	
	$(CC) $(C_FLAGS) $< -o $@

link:
	@echo 链接内核文件 $(C_OBJECTS)...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o kernel

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) kernel

.PHONY:update_image
update_image:
	cp kernel iso/boot/
	grub-mkrescue -o kernel.iso iso

.PHONY:mount_image
mount_image:
	sudo mount floppy.img /mnt/kernel

.PHONY:umount_image
umount_image:
	sudo umount /mnt/kernel

.PHONY:qemu
qemu:
	qemu -cdrom kernel.iso -boot a

.PHONY:bochs
bochs:
	bochs -f tools/bochsrc.txt

.PHONY:debug
debug:
	qemu -S -s -cdrom kernel.iso -boot a &
	sleep 1
	cgdb -x scripts/gdbinit
