MEMORY
{
  text   (rx)   : ORIGIN = 0x000000, LENGTH = 0x00ffff
  data   (rw!x) : ORIGIN = 0x010000, LENGTH = 0x00ffff
  .riscv.attributes (r) : ORIGIN = 0x030000, LENGTH = 0x00ffff
}

SECTIONS
{
  .text : { *(.text) }
  .data : { *(.data) }
  .riscv.attributes : { *(.riscv.attributes) }
}