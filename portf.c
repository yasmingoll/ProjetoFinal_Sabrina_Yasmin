#include "tm4c123gh6pm.h"

void PortF_Init(void)
{
  volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0xFF;    
  delay = SYSCTL_RCGC2_R;       
  GPIO_PORTF_LOCK_R = 0x4C4F434B;  
  GPIO_PORTF_CR_R = 0x1F;          
  GPIO_PORTF_AMSEL_R = 0;          
  GPIO_PORTF_PCTL_R = 0x00000000;  
  GPIO_PORTF_DIR_R |= 0x0E;      
  GPIO_PORTF_AFSEL_R &= ~0x1F;     
  GPIO_PORTF_PUR_R = 0x11;       
  GPIO_PORTF_DEN_R |= 0x1F;       
  GPIO_PORTF_DATA_R = 0x00;     
  GPIO_PORTF_IS_R &= ~0x01;     // (d) PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x01;    //     PF4 is not both edges
  GPIO_PORTF_IEV_R &= ~0x01;    //     PF4 falling edge event
  GPIO_PORTF_ICR_R = 0x01;      // (e) clear flag4
  GPIO_PORTF_IM_R |= 0x01;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;  
   
}
