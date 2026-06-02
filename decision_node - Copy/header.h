#ifndef HEADER_H
#define HEADER_H

#include <lpc21xx.h>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

/* ---------- CAN IDs ---------- */
#define ULTRASOUND     0x1AF
#define SWITCH_STATUS  0x1B0

/* ---------- L293D Pins ---------- */
#define L293D_PWM      (1<<8)    // P0.8 PWM6 (EN)
#define L293D_IN1      (1<<13)   // P0.13
#define L293D_IN2      (1<<14)   // P0.14

/* PINSEL bits for L293D direction pins (for GPIO mode) */
#define L293D_IN1_SEL  (3 << 26)   // P0.13 ? bits 27:26
#define L293D_IN2_SEL  (3 << 28)   // P0.14 ? bits 29:28

/* ---------- LCD Pins ---------- */
#define DATA 0xFF        // P0.0-P0.7
#define RS   (1<<9)      // P0.9
#define EN   (1<<10)     // P0.10

/* ---------- Motor safety & PWM thresholds ---------- */
#define DIST_SAFE    50
#define PWM_LOW      2500
#define PWM_MED      5000
#define PWM_HIGH     7500

/* ---------- CAN message struct ---------- */
typedef struct {
    u32 id;     // CAN ID
    u8  rtr;    // Remote Transmission Request
    u8  dlc;    // Data length code
    u32 dataA;  // First 4 bytes of data
    u32 dataB;  // Second 4 bytes of data
} CAN_MSG;

/* ---------- Global CAN message ---------- */
extern CAN_MSG msg;

/* ---------- Delay function ---------- */
void delay_ms(u32 t);

/* ---------- CAN functions ---------- */
void can_init(void);
void can_tx(CAN_MSG msg);
void can_rx(CAN_MSG *msg);
u8 can_rx_ready(void);

/* ---------- LCD functions ---------- */
void LCD_INIT(void);
void LCD_CMD(u8 cmd);
void LCD_DATA(u8 data);
void LCD_STR(char *s);
void LCD_NUM(u32 n);

#endif
