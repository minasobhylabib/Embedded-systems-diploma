
extern int main(void);

extern unsigned int _E_text;
extern unsigned int _s_data;
extern unsigned int _E_data;
extern unsigned int _s_bss;
extern unsigned int _E_bss;
extern unsigned int _stack_top;

void Reset_Handler(void)
{
unsigned int data_size = (unsigned int*) &_E_data - (unsigned int*) &_s_data;
unsigned int* P_src = (unsigned int*) &_E_text;
unsigned int* P_dst = (unsigned int*) &_s_data;
for(int i=0 ; i < data_size ; i++)
{
	* ((unsigned int*)P_dst++)= *((unsigned int*)P_src++);
}

unsigned int bss_size = (unsigned int*) &_E_bss - (unsigned int*) &_s_bss;
P_dst = (unsigned int*) &_s_bss;
for (int i=0 ; i < bss_size ; i++)
{
	*((unsigned int*)P_dst++) = (unsigned int)0;
}
main();
}
void Default_Handler(void)
{
	Reset_Handler();
}
void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));

void H_fault_Handler(void)__attribute__((weak,alias("Default_Handler")));
	
void MM_Fault_Handler(void)__attribute__((weak,alias("Default_Handler")));

void Bus_Fault(void)__attribute__((weak,alias("Default_Handler")));

void Usage_Fault_Handler(void)__attribute__((weak,alias("Default_Handler")));

	
unsigned int vectors[]__attribute__((section(".vectors"))) = {
 (unsigned int)&_stack_top,
(unsigned int)&Reset_Handler,
(unsigned int)&NMI_Handler,
(unsigned int)&MM_Fault_Handler,
(unsigned int)&Bus_Fault,
(unsigned int)&Usage_Fault_Handler};	

