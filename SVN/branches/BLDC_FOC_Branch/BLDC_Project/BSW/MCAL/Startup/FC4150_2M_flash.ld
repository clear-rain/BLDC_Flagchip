/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __data_init_start__
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
 

/* Entry Point */
ENTRY(Reset_Handler)


__vector_size = 0x0400;
HEAP_SIZE = 0x400;
STACK_SIZE = 0x400;

/* Specify the memory areas */
MEMORY
{
  /* Flash */
  FLASH                (RX)  : ORIGIN = 0x00000000, LENGTH = 2M

  /* SRAM_L */
  RAM_L                (RW)  : ORIGIN = 0x02000000, LENGTH = 64K
  
  /* SRAM_U */
  RAM_U                (RW)  : ORIGIN = 0x20000000, LENGTH = 192K
  
}

/* Define output sections */
SECTIONS
{

  /* The program code and other data goes into internal flash */
  .text :
  {
    . = ALIGN(1024); /* VTOR must be align to 1K */
    __interrupts_start__ = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    __interrupts_end__ = .;
    . = ALIGN(4);
        
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.init)                 /* section used in crti.o files */
    *(.fini)                 /* section used in crti.o files */
    *(.eh_frame)             /* section used in crtbegin.o files */
    . = ALIGN(4);
  } > FLASH

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    __data_init_start__ = .;
    
    .interrupts_ram :
  {
    . = ALIGN(1024); /* VTOR must be align to 1K */
    __vector_ram = .;
    __RAM_START = .;
    __interrupts_ram_start__ = .; /* Create a global symbol at data start. */
    *(.m_interrupts_ram)          /* This is a user defined section. */
    . += __vector_size;
    . = ALIGN(4);
    __interrupts_ram_end__ = .;   /* Define a global symbol at data end. */
  } > RAM_L
    
    .data : AT (__data_init_start__)
    {
        __data_start__ = .;
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > RAM_U

    .bss :
    {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > RAM_U

    .heap :
    {
        . = ALIGN(8);
        __HeapBegin = .;
        _end = .;
        end = _end;
        . += HEAP_SIZE;
        . = ALIGN(8);
        __HeapLimit = .;
    } > RAM_L

    .stack_dummy :
    {
        . = ALIGN(8);
        __StackLimit = .;
        . += STACK_SIZE;
        . = ALIGN(8);
        __StackTop = .;
    } > RAM_L


    __RAM_L_START__ = ORIGIN(RAM_L);
    __RAM_L_END__ = ORIGIN(RAM_L)+LENGTH(RAM_L)-1;
    
    __RAM_U_START__ = ORIGIN(RAM_U);
    __RAM_U_END__ = ORIGIN(RAM_U)+LENGTH(RAM_U)-1;
    
  .ARM.attributes 0 : { *(.ARM.attributes) }

  ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with STACK")
}

