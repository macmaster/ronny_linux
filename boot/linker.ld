/** linker.ld ***********************************
 * linker script to link the boot and kernl objs
 * 
 * Author: Ronald Macmaster
 * Date: 07/12/16
 ***********************************************/

/* layout the sections in the kernel image*/
ENTRY(_start)
SECTIONS {
	/* start the sections at 1MiB (convention) */
	. = 1M;

	/* place the multiboot header up front for bootloader */
	.text BLOCK(4K) : ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}

	/* read-only, read write, and stack data */
	.rodata BLOCK(4K) : ALIGN(4k) {
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K) {
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K) {
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}

}
