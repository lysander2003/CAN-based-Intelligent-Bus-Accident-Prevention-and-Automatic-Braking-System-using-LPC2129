#include "header.h"

CAN_MSG msg;  // global CAN message

void delay_us(u32 t){  // microsecond delay
    while(t--){ __asm("NOP"); }
}

/* ---------- Ultrasonic Read ---------- */
u32 read_ultrasonic(void){
    u32 dist, timeout;

    IODIR0 |= TRIG_PIN;      // TRIG = output
    IODIR0 &= ~ECHO_PIN;     // ECHO = input

    // Trigger pulse 10 us
    IOCLR0 = TRIG_PIN;
    delay_us(5);
    IOSET0 = TRIG_PIN;
    delay_us(10);
    IOCLR0 = TRIG_PIN;

    // Wait for echo high
    timeout = 30000;
    while(!(IOPIN0 & ECHO_PIN) && timeout--);
    if(timeout == 0) return 400;

    // Start timer
    T1TCR = 0x02; T1TC = 0; T1PR = 59; T1TCR = 0x01;

    // Wait for echo low
    timeout = 30000;
    while((IOPIN0 & ECHO_PIN) && timeout--);
    T1TCR = 0;

    if(timeout == 0) return 400;

    dist = T1TC / 58;   // distance in cm
    if(dist>400) dist = 400;
    return dist;
}

/* ---------- Main ---------- */
int main(void){
    CAN_MSG txmsg;

    can_init();
    txmsg.id = ULTRASOUND;
    txmsg.rtr = 0;
    txmsg.dlc = 4;           // must send full 4 bytes of u32
    txmsg.dataB = 0;

    while(1){
        txmsg.dataA = read_ultrasonic();
        can_tx(txmsg);       // transmit distance
        delay_ms(200);       // 5 Hz
    }
}
