#include "Spi.h"

void spi_init(spi_hardware_init*base,VOID_FPTR enable_l,VOID_FPTR enable_h,VOID_FPTR sclk_l,VOID_FPTR sclk_h,VOID_FPTR mosi_l,VOID_FPTR mosi_h,U8_FPTR get_miso,FPTR_U8 delayus,uint8_t delayuscount)
{
	base->enable_l = enable_l;//spi片选引脚
	base->enable_h = enable_h;//spi片选引脚
	base->sclk_l = sclk_l;//spi时钟引脚
	base->sclk_h = sclk_h;//spi时钟引脚
	base->mosi_l = mosi_l;//
	base->mosi_h = mosi_h;//
	base->get_miso = get_miso;//得到miso管脚电平1：高，0：低电平
	base->delayus = delayus;//延时阻塞函数，us级别
	base->delayuscount = delayuscount;//延时函数的阻塞时间，高低电平各自阻塞一次
	base->flag_busy = 0;
}
uint8_t spi_write_read(spi_hardware_init*base,uint8_t data)
{
	int8_t index;
	uint8_t  ret_data = 0;
	if(0 == base->flag_busy){
		base->flag_busy = 1;

		base->enable_h(); 
		
		base->sclk_l();      
		
		// 高位在前
		for (index = 7;index>=0;index--){

			if(0x01&(data>>index))
			{
				base->mosi_h();
			}else
			{
				base->mosi_l();
			}
			base->sclk_h();    
			base->delayus(base->delayuscount); 

			// low电平读取数据
			ret_data = (ret_data <<1) | (0x01&(base->get_miso()));  

			// 上升沿锁定数据
			base->sclk_l();
			base->delayus(base->delayuscount);
			
		}	
		base->sclk_l();
		
		base->enable_l();

		base->flag_busy = 0;
	}       
	return ret_data;
}

































































