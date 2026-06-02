#include "header.h"

void delay_ms(u32 t){
  T0PR=59999;
  T0TCR=0x02;
  T0TCR=0x01;
  while(T0TC<t);
  T0TCR=0;
}