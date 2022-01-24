MEMORY
{
	flash(RX) : ORIGIN = 0x00000000, LENGTH = 512M
	sram(rwx) : o = 0x20000000, l = 512M
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
	}> sram
	

}