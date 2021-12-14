#include <stdio.h>
#include <stdint.h> //
#include "portd.h"
#include "portd.c"
#include "portf.h"
#include "SysTick.h"
#include "Timer0.h"
#include "tm4c123gh6pm.h"
#include "PLL.c"



int control=0;
unsigned char estado = 0;
void SysTick_Wait1s(unsigned long delay)
{
  int i;
  for(i=0; i<delay; i++){
    SysTick_Wait(8000000);  //
  }
}
void Timer0A_Handler(void){
	
	Timer0_Off();	
	GPIO_PORTD_DATA_R = 0x00; //desaciona a lampada uv
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;		//Limpa Flag
	Timer0_Off();//desaciona timer0	
	control=1;//permite ir para próxima etapa
}

void GPIOPortF_Handler(void)
{
  GPIO_PORTF_ICR_R = 0x01;   
	if(estado==0)
	{
		estado=1;
	}
}
int main(void)
{         
	
	PLL_Init(Bus80MHz); //Liga clock para Hz por bloqueio de fase
  PortF_Init();
	PortD_Init();
	SysTick_Init();							// inicializa o systick
	unsigned char SW1;
		SW1 = GPIO_PORTF_DATA_R&0x10;
	while(1){
	switch(estado)
		{
			case (0):
						  GPIO_PORTF_DATA_R = 0;		// apaga LEDs
							GPIO_PORTD_DATA_R = 0;		// desliga relé	

							break;
			case (1):	
							GPIO_PORTF_DATA_R = 0x04;		// acende o LED azul //sinaliza que ligou
							SysTick_Wait1s(10);					// espera 1 s
							GPIO_PORTF_DATA_R = 0x00;				// apaga LEDs
							SysTick_Wait1s(10);	// 
							estado = 2;			
							break;

			case (2): // teste se chave fechada
							if ((GPIO_PORTF_DATA_R & 0x10) == 0) //se abriu a caixa
							{
								estado = 4; //vai pra estado 4
								
							}
							else
							{
								estado=3;

							}
							break;
			case (3):

							GPIO_PORTF_DATA_R =0x08;
							SysTick_Wait1s(80);					// espera 8 s
							estado = 1;   		// volta ao estado 1
							break;
			case (4):
							GPIO_PORTD_DATA_R = 0x04; //aciona a lampada uv
							GPIO_PORTF_DATA_R = 0x02;
							Timer0_Init(640000000); //inicia timer (640M/80M)
							estado=5;
							break;				
							
			case (5):
							if(control==1)
							{
								GPIO_PORTF_DATA_R = 0x00;
								estado=6;
							}
							break;	
			case (6): 
							GPIO_PORTD_DATA_R = 0x00; //desaciona a lampada uv
							for (int l=0; l<6; l++) //sinaliza lampada desligada
							{
								GPIO_PORTF_DATA_R = 0x02;
								SysTick_Wait1s(20);
								GPIO_PORTF_DATA_R = 0x00;
								SysTick_Wait1s(20);
							}
							estado=7;
							break;
		 case (7):
							// teste se chave aberta
							if ((GPIO_PORTF_DATA_R & 0x10) == 0) //se abriu a caixa
							{
								estado = 1; //volta pra estado 1
							}
							else
							{
								estado=8;
								GPIO_PORTF_DATA_R = 0x0C; // se não sinaliza
								SysTick_Wait1s(20);

							}
							break;
			case (8):
							
							GPIO_PORTF_DATA_R = 0x00;
							if ((GPIO_PORTF_DATA_R & 0x10) == 0) //verifica se a abriu a caixa
							{
								estado = 2; //vai para estado 2
							}
							else
							{
								estado = 9;
							}
							break;
			case (9):
							for (int i=0; i<4; i++)
							{
								GPIO_PORTF_DATA_R = 0x0E; //sinaliza
								SysTick_Wait1s(40);
								GPIO_PORTF_DATA_R = 0x00; 
								SysTick_Wait1s(40);
							}
							estado = 0; //volta para estado 0
							break;
						}
					}
			
			
		}
	


		
		
		

		
  

