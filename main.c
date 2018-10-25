#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <bcm2835.h>
#include "ltc68042_bcm.h"

#define TOTAL_IC 1
uint16_t cell_codes[TOTAL_IC][12];

int main(int argc, char **argv)
{
    int rdError = 0;
    printf("Raspberry Pi LTC6804-2 voltage test program\n");
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    LTC6804_initialize();
  while(1)
  {	
    LTC6804_adcv();
    rdError = LTC6804_rdcv(0, TOTAL_IC, cell_codes);
    if(rdError == -1){
	printf("A PEC error was detected in the received data\n");
	break;
    }
    else{
	for(int i=0; i<12; i++)
	{
	  printf("The voltage is %f\n", cell_codes[TOTAL_IC][i]*0.0001);
	  printf("%%%%%%%%%%%%%%%%%%%");
	}
    }
    bcm2835_delay(500);
  }
    return 0;
}
