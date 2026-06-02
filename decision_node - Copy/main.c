#include "header.h"

/* ---------- Global Variables ---------- */
CAN_MSG msg;        // CAN message
u32 distance = 999; // distance from Node1
u8 switches = 0;    // switch state from Node2
int speed = 0;      // PWM5 duty cycle

/* ---------- Delay ---------- */
//void delay_ms(u32 ms){
//    T0PR = 60000-1;   // 1ms resolution
//    T0TCR = 1;
//    while(T0TC < ms);
//    T0TCR = 3;
//    T0TCR = 0;
//}

/* ---------- LCD Functions ---------- */
void LCD_CMD(u8 cmd){ IOCLR0=DATA; IOSET0=cmd; IOCLR0=RS; IOSET0=EN; delay_ms(2); IOCLR0=EN; }
void LCD_DATA(u8 data){ IOCLR0=DATA; IOSET0=data; IOSET0=RS; IOSET0=EN; delay_ms(2); IOCLR0=EN; }
void LCD_STR(char *s){ while(*s) LCD_DATA(*s++); }
void LCD_NUM(u32 n){ char buf[6]; u8 i=0; if(n==0){LCD_DATA('0'); return;} while(n){ buf[i++]=(n%10)+'0'; n/=10;} while(i--) LCD_DATA(buf[i]); }
void LCD_INIT(void){
    IODIR0 |= DATA | RS | EN; 
    LCD_CMD(0x01); LCD_CMD(0x02); LCD_CMD(0x0C); LCD_CMD(0x38); LCD_CMD(0x80);
}

/* ---------- PWM5 Initialization ---------- */
void PWM5_Init(void){
    PINSEL1 &= ~(3<<10);   // Clear P0.21
    PINSEL1 |= (1<<10);    // Set P0.21 = PWM5
    PWMPR = 60-1;          // prescaler
    PWMMR0 = 0xFFF;        // PWM period
    PWMMCR = 0x02;         // reset on MR0
    PWMPCR = (1<<13);      // enable PWM5 output
    PWMTCR = 0x09;         // enable counter + PWM
}

/* ---------- Update PWM Duty Cycle ---------- */
void pwm_update(void){
    PWMMR5 = speed;        // set duty cycle
    PWMLER = (1<<5);       // latch MR5
}

/* ---------- L293D Motor Initialization ---------- */
void l293d_init(void){
    PINSEL0 &= ~(L293D_IN1_SEL | L293D_IN2_SEL); // GPIO mode
    IODIR0 |= L293D_IN1 | L293D_IN2;            // output
}

/* ---------- Motor Control ---------- */
void l293d_control(void){
    // Determine motor speed based on distance and switches
    if(distance < DIST_SAFE) speed = PWM_LOW;
    else{
        switch(switches & 0x07){
            case 4: speed = PWM_HIGH; break;
            case 2: speed = PWM_MED;  break;
            case 1: speed = PWM_LOW;  break;
            default: speed = 0;      break;
        }
    }

    pwm_update(); // update PWM5

    // Motor direction control
    if(speed){
        IOSET0 = L293D_IN1;
        IOCLR0 = L293D_IN2;
    } else {
        IOCLR0 = L293D_IN1 | L293D_IN2;
    }
}

/* ---------- CAN Read Function ---------- */
void read_can(void){
    while(can_rx_ready()){
        can_rx(&msg);
        if(!msg.rtr){
            if(msg.id == ULTRASOUND) distance = msg.dataA;
            if(msg.id == SWITCH_STATUS) switches = msg.dataA & 0x07;
        }
    }
}

/* ---------- LCD Display ---------- */
void display(void){
    LCD_CMD(0x80); LCD_STR("Dist:"); LCD_NUM(distance); LCD_STR("cm   ");
    LCD_CMD(0xC0); LCD_STR("SW:0x"); LCD_NUM(switches);
    if(distance < DIST_SAFE){ LCD_CMD(0x94); LCD_STR("SAFETY LOW!"); }
}

/* ---------- Main Function ---------- */
int main(void){
    can_init();
    PWM5_Init();
    l293d_init();
    LCD_INIT();

    LCD_CMD(0x80); 
	LCD_STR("V25CE2A2");
    delay_ms(1000);
	LCD_CMD(0X01);
	LCD_STR("BUS ACCIDENT PREVENTION");
	delay_ms(1000);
	LCD_CMD(0X01);

    while(1){
        read_can();        // get latest distance & switches
        l293d_control();   // control motor
        display();         // update LCD
        delay_ms(100);     // refresh 10 Hz
    }
}
