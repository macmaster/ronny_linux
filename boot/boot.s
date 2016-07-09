# boot.s
#
# kernel entry point for ronny_linux
# lot of reference to wiki.osdev.org/Bare_Bones
# and www.gnu.org/software/grub/manual/multiboot/multiboot.html
#
# Author: Ronny Macmaster
# Date: 07/08/2016

# multiboot header constants
.set ALIGN,		1<<0					# alignment modules within page boundaries
.set MEMINFO,	1<<1					# request memory map
.set FLAGS,		ALIGN or MEMINFO	# multiboot flag vector
.set MAGIC,		0x1BADB002			# magic id number to find header
.set CHECKSUM, -(MAGIC + FLAGS)	# unsigned checksum verify sums to 0
