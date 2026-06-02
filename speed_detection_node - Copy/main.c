#include "header.h"

int main(void){
    CAN_MSG txmsg;
    u8 switches, stable_switches;

    /* Configure P0.5,6,7 as INPUT */
    IODIR0 &= ~((1<<5)|(1<<6)|(1<<7));

    /* Initialize CAN */
    can_init();

    txmsg.id  = SWITCH_STATUS;
    txmsg.rtr = 0;
    txmsg.dlc = 1;

    while(1){
        /* First reading of switches */
        switches = 0;
        if(!(IOPIN0 & (1<<5))) switches |= 1;  // S1
        if(!(IOPIN0 & (1<<6))) switches |= 2;  // S2
        if(!(IOPIN0 & (1<<7))) switches |= 4;  // S3

        /* Only check if any switch is pressed */
        if(switches){
            delay_ms(200);  // debounce delay

            /* Second reading to confirm stable press */
            stable_switches = 0;
            if(!(IOPIN0 & (1<<5))) stable_switches |= 1;
            if(!(IOPIN0 & (1<<6))) stable_switches |= 2;
            if(!(IOPIN0 & (1<<7))) stable_switches |= 4;

            /* Only send if stable */
            if(stable_switches == switches){
                txmsg.dataA = stable_switches;
                can_tx(txmsg);
            }
        }

        delay_ms(50);  // small delay to avoid continuous looping
    }
}
