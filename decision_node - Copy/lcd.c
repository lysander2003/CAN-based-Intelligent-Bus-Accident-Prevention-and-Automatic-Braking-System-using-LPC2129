//#include "header.h"

//void lcd_cmd(u8 cmd){
//  IOCLR0=LCD_RS|LCD_RW;
//  IOPIN0=(IOPIN0&~LCD_PORT)|(cmd&0xFF);
//  IOSET0=LCD_EN; delay_ms(1); IOCLR0=LCD_EN; delay_ms(2);
//}
//
//void lcd_data(u8 dat){
//  IOSET0=LCD_RS; IOCLR0=LCD_RW;
//  IOPIN0=(IOPIN0&~LCD_PORT)|(dat&0xFF);
//  IOSET0=LCD_EN; delay_ms(1); IOCLR0=LCD_EN; delay_ms(1);
//}
//
//void lcd_init(void){
//  IODIR0 |= LCD_PORT;
//  delay_ms(20);
//  lcd_cmd(0x38); lcd_cmd(0x0C); lcd_cmd(0x06); lcd_cmd(0x01);
//}
//
//void lcd_str(char *s){
//  while(*s) lcd_data(*s++);
//}
//
//void lcd_num(u32 n){
//  char buf[6]; u8 i=0;
//  if(n==0){ lcd_data('0'); return; }
//  while(n){ buf[i++]=n%10+'0'; n/=10; }
//  while(i--) lcd_data(buf[i]);
//}
