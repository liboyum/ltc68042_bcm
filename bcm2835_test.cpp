#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>

int main()
{
	if(!bcm2835_init())
	{
		printf("bcm2835_init failed. Are you running as root?\n");
		return 1;
	}
	if(!bcm2835_spi_begin())
	{
		printf("bcm2835_spi_begin failed. Are you running as root?\n");
		return 1;
	}
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
	//ADCV command for cell 1&7
	uint8_t comm0 = 0x03;
	uint8_t comm1 = 0x61;
	uint8_t pec0 = 0x7f;
	uint8_t pec1 = 0x5e;
	bcm2835_spi_transfer(comm0);
	bcm2835_spi_transfer(comm1);
	bcm2835_spi_transfer(pec0);
	bcm2835_spi_transfer(pec1);
	//RDCV command for cell 1&7
	uint8_t rdcmd0 = 0x00;
	uint8_t rdcmd1 = 0x04;
	uint8_t pec2 = 0x07;
	uint8_t pec3 = 0xc2;
	bcm2835_spi_transfer(rdcmd0);
	bcm2835_spi_transfer(rdcmd1);
	bcm2835_spi_transfer(pec2);
	bcm2835_spi_transfer(pec3);
	
	uint8_t cell_data[2];
	cell_data[0] = bcm2835_spi_transfer(0xFF);
	cell_data[1] = bcm2835_spi_transfer(0xFF);
	
	printf("%f\n", cell_data[0]);
	printf("%f\n", cell_data[1]);
	
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}
