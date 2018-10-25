#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <bcm2835.h>
#include "ltc68042_bcm.h"

const uint8_t TOTAL_IC = 1;
uint16_t cell_codes[TOTAL_IC][12];
uint8_t tx_cfg[TOTAL_IC][6];
int rdError = 0;

int main(int argc, char **argv)
{
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
    for(int i = 0; i<TOTAL_IC;i++)
    {
      tx_cfg[i][0] = 0xFE;
      tx_cfg[i][1] = 0x00 ; 
      tx_cfg[i][2] = 0x00 ;
      tx_cfg[i][3] = 0x00 ; 
      tx_cfg[i][4] = 0x00 ;
      tx_cfg[i][5] = 0x00 ;
    }
  while(1)
  {	
    LTC6804_wrcfg(TOTAL_IC,tx_cfg);
    LTC6804_adcv();
    rdError = LTC6804_rdcv(0, TOTAL_IC, cell_codes);
    if(rdError == -1){
	printf("A PEC error was detected in the received data\n");
	break;
    }
    else{
	for(int i=0; i<12; i++)
	{
		printf("The voltage is %f\n", cell_codes[TOTAL_IC][i]);
	}
    }
    bcm2835_delay(500);
  }
    return 0;
}
