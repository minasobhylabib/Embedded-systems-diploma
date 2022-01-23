MEMORY
{
	flash(RX) : ORIGIN = 0x08000000, LENGTH = 128K
	sram(rwx) : o = 0x20000000, l = 20K
}
SECTIONS
{
	.text :
	{	*(.vectors*)
		*(.text*)
		*(.rodata*)
		_E_text = . ;
	}> flash
	.data :
	{	_s_data = . ;
		*(.data*)
		. = ALIGN(4);
		_E_data = . ;
	}>sram AT> flash
	.bss :
	{	_s_bss = . ;
		*(.bss*)
		. = ALIGN(4);
		_E_bss = . ;
		. = . + 0x1000;
		_stack_top = .;
	}> sram
	

}