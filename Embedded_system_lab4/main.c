
#include <stdlib.h>
typedef volatile unsigned int vuint32_t;

#define RCC_BASE          0x40021000
#define RCC_APB2ENR       *(vuint32_t*)(RCC_BASE + 0x18)
#define GPIOA_BASE        0x40010800
#define GPIOA_CRH         *(vuint32_t*)(GPIOA_BASE + 0x4)
#define GPIOA_ODR         *(vuint32_t*)(GPIOA_BASE + 0x0c)
#include "stdlib.h"
typedef union 
{
	vuint32_t  all_fields;
	struct
	{
		vuint32_t reserved:13;
		vuint32_t P_13:1;
	}Pin;
}R_ODR_t;

void* _sbrk(int incr)
{
	static unsigned char* heap_ptr = NULL;
	unsigned char* prev_heap_ptr = NULL;
	extern unsigned int _E_bss;
	extern unsigned int _heap_End;
	if(heap_ptr ==NULL)
		heap_ptr = (unsigned char*)&_E_bss;
	prev_heap_ptr = heap_ptr;
	if((heap_ptr + incr) > ( (unsigned char*)&_heap_End))
		return (void*) NULL;
	heap_ptr += incr;
	return (void*) prev_heap_ptr;
}

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0c);
volatile unsigned char b[3];
volatile unsigned char g[3]={1,2,3};
unsigned char const const_variables[3] = {1,2,3}; 
int main(void)
{
	
	int* p= (int*)malloc(sizeof(int));
	RCC_APB2ENR = RCC_APB2ENR | (1<<2);
	GPIOA_CRH = GPIOA_CRH & 0xff0fffff;
	GPIOA_CRH = GPIOA_CRH | 0x00200000;
	int i; 
	while(1)
	{
		
		R_ODR-> Pin.P_13 =1;
		for(i=0;i<5000;i++);
		R_ODR-> Pin.P_13 =0;
		for(i=0;i<5000;i++);
		
	}
	free (p);
}