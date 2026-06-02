//#include "header.h"
//
//u32 distance=999;
//u8 switches=0;

//void l293d_init(void){
//  PINSEL0 &= ~((1<<26)|(1<<27)|(1<<28));
//  IODIR0  |= L293D_IN1|L293D_IN2;
//}
//
//void l293d_control(void){
//  u32 pwm_val=0;
//  
//  // SAFETY FIRST
//  if(distance < DIST_SAFE){
//    pwm_val = PWM_LOW;
//  }else{
//    switch(switches&0x07){
//      case 4: pwm_val=PWM_HIGH; break;
//      case 2: pwm_val=PWM_MED;  break;
//      case 1: pwm_val=PWM_LOW;  break;
//      default: pwm_val=0; break;
//    }
//  }
//  
//  PWMMR5=pwm_val;
//  PWMLER=(1<<5);
//  
//  if(pwm_val){
//    IOSET0=L293D_IN1;  // Forward
//    IOCLR0=L293D_IN2;
//  }else{
//    IOCLR0=L293D_IN1|L293D_IN2;  // STOP
//  }
//}
