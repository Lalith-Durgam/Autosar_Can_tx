#include<stdio.h>
#include"com_send.h"
void com_send(uint8_t signal_data[8],unsigned char sig_name[3])
{
    uint8_t D[8];
    unsigned char *sig_type;
    D[0]=signal_data[0];
    D[1]=signal_data[1];
    D[2]=signal_data[2];
    D[3]=signal_data[3];
    D[4]=signal_data[4];
    D[5]=signal_data[5];
    D[6]=signal_data[6];
    D[7]=signal_data[7];
    sig_type=sig_name;
    
    
    
    void pdur_send( D, sig_type);
}
