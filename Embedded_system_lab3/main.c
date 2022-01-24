typedef volatile unsigned int vuint32_t;
typedef unsigned int           uint32_t;
#define SYSCTL_RGGC2_R       *(vuint32_t*)(0X400FE000 + 0X108)
#define GPIO_PORTF_DIR_R     *(vuint32_t*)(0X40025000+0X400)
#define GPIO_PORTF_DEN_R     *(vuint32_t*)(0X40025000+0X51C)
#define GPIO_PORTF_DATA_R    *(vuint32_t*)(0X40025000+0X3FC)

 
int main(void)
{
	SYSCTL_RGGC2_R = 0X20;
	//DELAY
	vuint32_t delay_count;
	for(delay_count=0;delay_count<200;delay_count++);
	GPIO_PORTF_DEN_R = 1<<3;
	GPIO_PORTF_DIR_R = 1<<3;
	while(1)
	{
		GPIO_PORTF_DATA_R |=1 << 3 ;
		for(delay_count=0;delay_count<5000;delay_count++);
		GPIO_PORTF_DATA_R &= ~(1 << 3) ;
		for(delay_count=0;delay_count<5000;delay_count++);
	
	}
	return 0;

}