#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BAUDRATE_SET_FX29 400000

 void i2c_init()
 {
     bcm2835_i2c_begin();
     bcm2835_i2c_set_baudrate(BAUDRATE_SET_FX29);
 }

 int fx29_lecture(int fx29_No)
 {
        uint8_t FX29_address_A = 0x28;
        uint8_t FX29_address_B = 0x28;

        int i;

        int len = 2;
        char buf[2];
        uint8_t data;

        switch (fx29_No)
        {
            case 1: bcm2835_i2c_setSlaveAddress(FX29_address_A);

            case 2: bcm2835_i2c_setSlaveAddress(FX29_address_B);

            default : return(-1);
        }

            data = bcm2835_i2c_read ( buf, len);

            printf("Read Result = %d\n", data);

            for (i=0;i<16;i++) printf("%c\n",buf[i])
 }
