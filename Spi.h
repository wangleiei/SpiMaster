#ifndef _mspi
#define _mspi

#include "stm8l15x.h"

typedef void(*VOID_FPTR)(void);
typedef uint8_t(*U8_FPTR)(void);
typedef void(*FPTR_U8)(uint8_t);
// spi_hardware_init spi_hardware_init;
typedef struct spi_hardware_init
{
	VOID_FPTR enable_l;
	VOID_FPTR enable_h;
	VOID_FPTR sclk_l;
	VOID_FPTR sclk_h;
	VOID_FPTR mosi_l;
	VOID_FPTR mosi_h;
	U8_FPTR get_miso;
	FPTR_U8 delayus;
	uint8_t delayuscount;
	uint8_t flag_busy;
}spi_hardware_init;



void spi_write_byte(spi_hardware_init *base,
	uint8_t  b);
uint8_t  spi_read_byte(spi_hardware_init *base);
void spi_write (spi_hardware_init *base,
	uint8_t * buf,
	uint32_t len);
void spi_read(spi_hardware_init *base,
	uint8_t * buf,
	uint32_t len);
uint8_t spi_write_read(spi_hardware_init *base,
	uint8_t data);
void spi_init(spi_hardware_init*base,
	// VOID_FPTR enable_l,
	// VOID_FPTR enable_h,
	VOID_FPTR sclk_l,
	VOID_FPTR sclk_h,
	VOID_FPTR mosi_l,
	VOID_FPTR mosi_h,
	U8_FPTR get_miso,
	FPTR_U8 delayus,
	uint8_t delayuscount);
#endif