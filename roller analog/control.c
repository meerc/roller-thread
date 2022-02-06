
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcp4822.h"
#include "I2C.h"
#include <bcm2835.h>
#include <sched.h>

#define BAUDRATE_SET_FX29 400000

int lecture ();

/* la fonction sert a controlé le signa de cna pour controler l'ecs*/
void * control()
{
    int Valmv;

    while(bcm2835_gpio_lev(pinIn) == 1)
    {
        /*je lis et je transforme les valeurs reçus des capteurs pour les ramener a
                                              un référencielle de 4000 */
         Valmv=lecture();

    // je genere un signal analogique avec le canal A du CNA mcp 4822.
        mcp4822_set_voltage (MCP_4822_CHANNEL_A,Valmv);
    }
}


int lecture ()
{
    int Cap[2];
    int data;

    for (i=0;i<2;i++) Cap[i]= fx29_lecture(i+1);

    data= Cap[0]-Cap[1];
    if(data<>0)
    {
    data= 1/(data/7);
    data= data*data*data;
    data= (data*2000)+2000;
    }
    else
    {
        data=2000;
    }

    return data
}
