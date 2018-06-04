	/* Entry Point */
	ENTRY(reset_addr)

	/* Specify the memory areas */
	MEMORY
	{
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 0x100000 /* 1024 K */
	RAM (rwx)	: ORIGIN = 0x20000000, LENGTH = 0x018000 /* 96 K */
	RAM2 (rwx)	: ORIGIN = 0x10000000, LENGTH = 0x008000 /* 32 K */

	}

	stack_size = 1024;
	_stack_start = ORIGIN(RAM2)+LENGTH(RAM2);
	_stack_end = _stack_start - stack_size;

	heap_size = 256;

	/* Define output sections */
	SECTIONS
	{
		.text :
		{
			. = ALIGN(4);
			*(.startup)		/* .startup section */
			*(.text)		/* .text sections (code) */
			*(.text*)		/* .text* sections (code) */
			*(.libs)		/* .libs sections (code) */
			*(.rodata)		/* .rodata sections (constants, strings, etc.) */
			*(.rodata*)		/* .rodata* sections (constants, strings, etc.) */
			. = ALIGN(4);
			_etext = .;		/* define a global symbols at end of code */
		} >FLASH

		.ARM.extab	: { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
		.ARM : 
		{
			__exidx_start = .;
			*(.ARM.exidx*)
			__exidx_end = .;
		} >FLASH

		/* used by the startup to initialize data */
		_sidata = .;

		/* Initialized data sections goes into RAM, load LMA copy after code */
		.data : AT ( _sidata )
		{
			. = ALIGN(4);
			_sdata = .;		/* create a global symbol at data start */
			*(.data)		/* .data sections */
			*(.data*)		/* .data* sections */

			. = ALIGN(4);
			_edata = .;		 /* define a global symbol at data end */
		} >RAM

		/* Uninitialized data section */
		. = ALIGN(4);
		.bss :
		{
			/*  Used by the startup in order to initialize the .bss secion */
			_sbss = .;			/* define a global symbol at bss start */
			__bss_start__ = _sbss;
			*(.bss)
			*(.bss*)
			*(COMMON)

			. = ALIGN(4);
			_ebss = .;			/* define a global symbol at bss end */
			__bss_end__ = _ebss;
		} >RAM

		. = ALIGN(4);
		.heap :
		{
		 _heap_start = .;
		 . = . + heap_size;
		_heap_end = .;
		} > RAM

		.ram2 :
		{
			. = ALIGN(4);
			_sram2 = .;
			*(.ram2)
			. = ALIGN(4);
			_eram2 = .;
		} > RAM2

	 	.ARM.attributes 0 : { *(.ARM.attributes) }
	}

