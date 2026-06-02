#ifndef HEADER_H
#define HEADER_H
#include <lpc21xx.h>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

#define ULTRASOUND     0x1AF
#define SWITCH_STATUS  0x1B0

// Ultrasonic Pins
#define TRIG_PIN     (1<<22)
#define ECHO_PIN     (1<<21)

// L293D Pins (RECEIVER ONLY)
#define L293D_PWM    (1<<8)   // P0.8 PWM6 ? Enable Pin1
#define L293D_IN1    (1<<13)  // P0.13 ? Input1 Pin2
#define L293D_IN2    (1<<14)  // P0.14 ? Input2 Pin7

// LCD 8-bit (RECEIVER ONLY) P0.0-12
#define LCD_RS       (1<<10)
#define LCD_RW       (1<<11) 
#define LCD_EN       (1<<12)
#define LCD_PORT     0x00001FFF  // P0.0-12

#define DIST_SAFE    50
#define PWM_LOW      2500
#define PWM_MED      5000
#define PWM_HIGH     7500

typedef struct{
  u32 id;
  u8 rtr;
  u8 dlc;
  u32 dataA;
  u32 dataB;
} CAN_MSG;

void delay_ms(u32 t);
void can_init(void);
void can_tx(CAN_MSG msg);
void can_rx(CAN_MSG *msg);
u8 can_rx_ready(void);

#endif