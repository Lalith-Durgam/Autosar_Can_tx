#include<stdio.h>
#include"can_if_config.h"
#include"can_if.h"
#include"can_tx.h"
void can_init()
{
TRISBbits.RB2=0;
TRISBbits.RB3=1;
}
void can_tx_config(uint8_t mode)
{
CANCON=mode;
while(CANCON!=0x80);
   BRGCON1 = 0xC1;   //Baud rate 250Kbps
    BRGCON2 = 0xAE;  
    BRGCON3 = 0x45;
    CIOCON=0x20;
    CANCON=0x08;
    
}
void can_tx_drv(msg1)
{
can_init();
can_tx_config(0x80);
TXB0SIDH=(msg1.ID>>3)&(0xFF);
TXB0SIDH=(msg1.ID<<5)&(0xFF);
TXB0DLC=msg1.DLC;
TXB0D0=msg1.d[0];
TXB0D1=msg1.d[1];
TXB0D2=msg1.d[2];
TXB0D3=msg1.d[3];
TXB0D4=msg1.d[4];
TXB0D5=msg1.d[5];
TXB0D6=msg1.d[6];
TXB0D7=msg1.d[7];
TXB0CON=0x08;
}
