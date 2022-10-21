/*
 * File:   main.c
 * Author: dl70391
 *
 * Created on October 21, 2022, 8:24 AM
 */

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = BOHW     // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (VBOR set to 2.1V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config PBADEN = OFf      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config BBSIZ = 1024     // Boot Block Size Select bits (1K words (2K bytes) Boot Block)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

void swc_1();
void com_send(uint8_t signal_data[8],unsigned char sig_name[3]);
void pdur_send(unsigned char D[8],unsigned char *sig_type);
void can_if(msg1);
void can_tx_drv(msg1);
void spi_handler_drv(unsigned char ext_data);
void pdur_config(unsigned char msg);


void main(void) {
    swc_1();
    return 0;
}


void swc_1()
{

    unsigned char sig_name[4]="s_eg";
uint8_t signal_data[8];
signal_data[0]=0x23;
signal_data[1]=0x34;
signal_data[2]=0x45;
signal_data[3]=0x56;
signal_data[4]=0x67;
signal_data[5]=0x78;
signal_data[6]=0x89;
signal_data[7]=0x90;





com_send(signal_data,sig_name);  //sig_eng,100
}

/**/
/*
void com_send(uint8_t signal_data[8],unsigned char sig_name[3]) // sig,x
{


pdur_send(signal_data);
}

//////////////////////

void pdur_send(uint8_t *D)
{
uint16_t ID;
uint8_t DLC;
ID=pdur_config(D);
can_if_send(ID,D,DLC);
} 

///////////////////

void can_if_send(uint16_t ID,uint8_t *D,uint8_t DLC)
{
uint8_t block;
block=can_if_config(ID);
if(block ==0)
{
can_send_drv(ID,D,DLC);
}
elseif(block==1)
{
ext_can_drv(ID,D,DLC);
}
}

/////////////////

void ext_can_drv(uint16_t ID,uint8_t *D,uint8_t DLC)
{

spi_handler_drv(ID);
spi_handler_drv(D[0]);
spi_handler_drv(D[1]);
spi_handler_drv(D[2]);
spi_handler_drv(D[3]);
spi_handler_drv(D[4]);
spi_handler_drv(D[5]);
spi_handler_drv(D[6]);
spi_handler_drv(D[7]);
spi_handler_drv(D[8]);
}

///// 
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

void can_send_drv(uint16_t ID, uint8_t *D,uint8_t DLC)
{
can_init();
can_tx_config(0x80);
TXB0SIDH=(ID>>3)&(0xFF);
TXB0SIDH=(ID<<5)&(0xFF);
TXB0DLC=DLC;
TXB0D0=D[0];
TXB0D1=D[1];
TXB0D2=D[2];
TXB0D3=D[3];
TXB0D4=D[4];
TXB0D5=D[5];
TXB0D6=D[6];
TXB0D7=D[7];
TXB0CON=0x08;
}



*/

