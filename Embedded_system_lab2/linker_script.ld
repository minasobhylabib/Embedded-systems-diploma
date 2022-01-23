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
	}> flash
	.data :
	{	*(.data)
	}>flash
	.bss :
	{*(.bss*)
	} > sram

}