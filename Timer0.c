#include "tm4c123gh6pm.h"

void Timer0_Init(unsigned long t){
	volatile unsigned long tempo;
  SYSCTL_RCGCTIMER_R |= 0x01;   
  tempo = SYSCTL_RCGCTIMER_R;		
	TIMER0_CTL_R = 0x00000000;    
  TIMER0_CFG_R = 0x00000000;   
  TIMER0_TAMR_R = 0x00000002;   
  TIMER0_TAILR_R = t-1;    
  TIMER0_TAPR_R = 0;            
  TIMER0_ICR_R = 0x00000001;  
  TIMER0_IMR_R = 0x00000001;    
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; 
	NVIC_EN0_R = 1<<19;      
  TIMER0_CTL_R = 0x00000001;   
}
void Timer0_Off(void)
{
		TIMER0_CTL_R = 0x00000000;    
}
