# makefile
# build routines for ronny_linux
# 
# Author: Ronny Macmaster
# Date: 07/19/16

# var defs
src = boot
isodir = burn
obj = $(src)/boot.o $(src)/kernel.o 
link = $(src)/linker.ld

cgcc = i686-elf-gcc # cross compiler
cas = i686-elf-as # cross assembler

# burn ronny_linux to a ronny.iso CD img
ronny : $(obj) $(link)
	$(cgcc) -T $(link) -o $(src)/ronny.bin \
	-ffreestanding -O2 -nostdlib $(obj) -lgcc
	
	echo 'menuentry "ronny_linux" {' > grub.cfg
	echo '	multiboot /boot/ronny.bin' >> grub.cfg
	echo '}' >> grub.cfg
	
	mkdir -p $(isodir)/boot/grub
	mv boot/ronny.bin $(isodir)/boot
	mv grub.cfg $(isodir)/boot/grub
	grub-mkrescue -o ronny.iso $(isodir)
	
$(src)/boot.o : $(src)/boot.s
	$(cas) -o $(src)/boot.o $(src)/boot.s

$(src)/kernel.o : $(src)/kernel.c
	$(cgcc) -o $(src)/kernel.o -c $(src)/kernel.c \
	-ffreestanding -O2 -std=gnu99 -Wall -Wextra

clean : 
	rm -rf $(isodir)
	rm $(src)/*.o
	rm ronny.iso

