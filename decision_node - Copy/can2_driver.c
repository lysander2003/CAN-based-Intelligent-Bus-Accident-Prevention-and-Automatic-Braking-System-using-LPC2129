#include "header.h"

/* Global CAN message */
//CAN_MSG msg;

/* Initialize CAN2 */
void can_init(void){
    PINSEL1 |= 0x00014000;  // P0.23-TD2, P0.24-RD2
    VPBDIV = 1;

    C2MOD = 1;             // Reset
    AFMR  = 2;             // Accept all
    C2BTR = 0x001C001D;    // 125 Kbps
    C2MOD = 0;             // Normal operation
}

/* Transmit CAN message */
void can_tx(CAN_MSG m){
    C2TID1 = m.id;
    C2TFI1 = (m.dlc << 16);

    if(!m.rtr){
        C2TFI1 &= ~(1<<30);
        C2TDA1 = m.dataA;
        C2TDB1 = m.dataB;
    }

    C2CMR = 0x21;  // Transmit request
    while(!(C2GSR & 8));
}

/* Receive CAN message */
void can_rx(CAN_MSG *m){
    while(!(C2GSR & 1));  // wait for message

    m->id  = C2RID;
    m->dlc = (C2RFS >> 16) & 0xF;
    m->rtr = (C2RFS >> 30) & 1;

    if(!m->rtr){
        m->dataA = C2RDA;
        m->dataB = C2RDB;
    }

    C2CMR = 4;
}


/* Check if CAN message is ready */
u8 can_rx_ready(void){
    return (C2GSR & 1);
}
