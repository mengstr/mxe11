/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-powerpc", "elf32-powerpc","elf32-powerpc")
OUTPUT_ARCH(powerpc:common)
ENTRY(_start)
SEARCH_DIR("/usr/local/powerpc-vle-elf/lib");

_reset_address		= 0x0000;
__irq_stack_size__	= 0x0000; /* Not yet used.*/
__process_stack_size__	= 0x0000;

MEMORY
{
	flash		: org = 0x00000000, len = 1024k
	ram		: org = 0x40000000, len = 128k
}

ENTRY(_reset_address)

/*
 * Derived constants.
 */
__flash_size__		= LENGTH(flash);
__flash_start__		= ORIGIN(flash);
__flash_end__		= ORIGIN(flash) + LENGTH(flash);

__ram_size__		= LENGTH(ram);
__ram_start__		= ORIGIN(ram);
__ram_end__		= ORIGIN(ram) + LENGTH(ram);

SECTIONS
{
	. = ORIGIN(flash);

	.text : ALIGN(16) SUBALIGN(16)
	{
		*(.startup)
		. = ALIGN(0x0000800);
		*(.text)
		*(.text.*)
		*(.gnu.linkonce.t.*)
	} > flash

	.rodata : ALIGN(16) SUBALIGN(16)
	{
		*(.glue_7t)
		*(.glue_7)
		*(.gcc*)
		*(.rodata)
		*(.rodata.*)
		*(.rodata1)
	} > flash

	.sdata2 : ALIGN(16) SUBALIGN(16)
	{
		__sdata2_start__ = . + 0x8000;
		*(.sdata2)
		*(.sdata2.*)
		*(.gnu.linkonce.s2.*)
		*(.sbss2)
		*(.sbss2.*)
		*(.gnu.linkonce.sb2.*)
	} > flash

	.romdata : ALIGN(16) SUBALIGN(16)
	{
		__romdata_start__ = .;
	} > flash


	.stacks :
	{
		. = ALIGN(8);
		__irq_stack_base__ = .;
		. += __irq_stack_size__;
		. = ALIGN(8);
		__irq_stack_end__ = .;
		__process_stack_base__ = .;
		__main_thread_stack_base__ = .;
		. += __process_stack_size__;
		. = ALIGN(8);
		__process_stack_end__ = .;
		__main_thread_stack_end__ = .;
	} > ram

	.data : AT(__romdata_start__)
	{
		. = ALIGN(4);
		__data_start__ = .;
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d.*)
		__sdata_start__ = . + 0x8000;
		*(.sdata)
		*(.sdata.*)
		*(.gnu.linkonce.s.*)
		__data_end__ = .;
	} > ram

	.sbss :
	{
		__bss_start__ = .;
		*(.sbss)
		*(.sbss.*)
		*(.gnu.linkonce.sb.*)
		*(.scommon)
	} > ram

	.bss :
	{
		*(.bss)
		*(.bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)
		__bss_end__ = .;
	} > ram

	__heap_base__   = __bss_end__;
	__heap_end__	= __ram_end__;
}

