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
    	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);   // The default
    	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
	//ADCV command for all cell 
	uint8_t comm0 = 0x03;
	uint8_t comm1 = 0x60;
	uint8_t pec0 = 0xF4;
	uint8_t pec1 = 0x6C;
	bcm2835_spi_transfer(comm0);
	bcm2835_spi_transfer(comm1);
	bcm2835_spi_transfer(pec0);
	bcm2835_spi_transfer(pec1);

	//RDCV command for cell group A
	uint8_t rdcmd0 = 0x80;
	uint8_t rdcmd1 = 0x04;
	uint8_t pec2 = 0x77;
	uint8_t pec3 = 0xD6;
	bcm2835_spi_transfer(rdcmd0);
	bcm2835_spi_transfer(rdcmd1);
	bcm2835_spi_transfer(pec2);
	bcm2835_spi_transfer(pec3);
	
	uint8_t cell_data[8];
	cell_data[0] = bcm2835_spi_transfer(0x00);
	cell_data[1] = bcm2835_spi_transfer(0x00);
	cell_data[2] = bcm2835_spi_transfer(0x00);
	cell_data[3] = bcm2835_spi_transfer(0x00);
	cell_data[4] = bcm2835_spi_transfer(0x00);
	cell_data[5] = bcm2835_spi_transfer(0x00);
	cell_data[6] = bcm2835_spi_transfer(0x00);
	cell_data[7] = bcm2835_spi_transfer(0x00);
	
	uint16_t cell_codes[3];
	cell_codes[0] = cell_data[0] + (cell_data[1]<<8);
	cell_codes[1] = cell_data[2] + (cell_data[3]<<8);
	cell_codes[2] = cell_data[4] + (cell_data[5]<<8);
	
	printf("%d\n", cell_codes[0]);
	printf("%d\n", cell_codes[1]);
	printf("%d\n", cell_codes[2]);

	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}
