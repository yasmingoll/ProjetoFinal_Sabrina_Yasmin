#include "tm4c123gh6pm.h"

void PortD_Init(void){
  volatile uint32_t delay;
	SYSCTL_RCGC2_R |= 0xFF; 		// activate clock for port B
  delay=SYSCTL_RCGC2_R;           	// delay
  GPIO_PORTD_AMSEL_R = 0x00;      	// disable analog functionality on PB
  GPIO_PORTD_PCTL_R = 0x0000000; 		// configure PB as GPIO
  GPIO_PORTD_DIR_R = 0xFF;     			// make PB out
  GPIO_PORTD_AFSEL_R = 0x00;  			// disable alt funct on PB
  GPIO_PORTD_DEN_R = 0xFF;  	   		// enable digital I/O on PB
  GPIO_PORTD_DATA_R = 0x00;   			// PB = 0x00
}
