#include <stdint.h>
#include "PLL.h"
#include "tm4c123gh6pm.h"

#define SYSCTL_RIS_PLLLRIS      0x00000040  
#define SYSCTL_RCC_XTAL_M       0x000007C0  
#define SYSCTL_RCC_XTAL_6MHZ    0x000002C0  
#define SYSCTL_RCC_XTAL_8MHZ    0x00000380 
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540  
#define SYSCTL_RCC2_USERCC2     0x80000000  
#define SYSCTL_RCC2_DIV400      0x40000000  
                                            
#define SYSCTL_RCC2_SYSDIV2_M   0x1F800000  
#define SYSCTL_RCC2_SYSDIV2LSB  0x00400000  
#define SYSCTL_RCC2_PWRDN2      0x00002000  
#define SYSCTL_RCC2_BYPASS2     0x00000800  
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070  
#define SYSCTL_RCC2_OSCSRC2_MO  0x00000000  

void PLL_Init(uint32_t freq){
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;

  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;

  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;

  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) 
                  + (freq<<22);   
 
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};

  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

