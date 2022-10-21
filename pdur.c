#include<stdio.h>
#include"pdur.h"
#include"pdur_config.h"
void pdur_send(unsigned char D[8],unsigned char *sig_type)
{
    pdur_config(sig_type,D);
       msg1.d=D;
      
       can_if(msg1);
}
