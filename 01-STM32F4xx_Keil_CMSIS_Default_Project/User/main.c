#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include <stdio.h>
 uint32_t gj=0;
 #include "tm_stm32f4_spi.h"
 void SPI1_IRQHandler (void) {
  if (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==SET) {
    // Прерывание вызвано приемом байта ?
    uint8_t data = SPI1->DR; //Читаем то что пришло
//    GPIOC->ODR ^= (GPIO_Pin_9 | GPIO_Pin_8); //Инвертируем состояние светодиодов
    SPI1->DR = 0x65; //И отправляем обратно то что приняли
		SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_RXNE);
		if(data==0x99)
		{
		GPIO_SetBits(GPIOG,GPIO_Pin_13);
		}
  }
}
  void  TM_SPI_Init1(void)
    {
GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;
  //Тактирование порта со светодиодами
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOC , &GPIO_InitStructure);
  // Тактирование модуля SPI1 и порта А
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    //Initialize pins
    GPIO_Init(GPIOG, &GPIO_InitStructure);
		
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    //Initialize pins
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  // Настраиваем ноги SPI1 для работы в режиме альтернативной функции
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //Заполняем структуру с параметрами SPI модуля
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //полный дуплекс
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // передаем по 8 бит
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // Полярность и
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // фаза тактового сигнала
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard; // Управлять состоянием сигнала NSS аппаратно
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; // Предделитель SCK
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // Первым отправляется старший бит
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave; // Режим - слейв
  SPI_Init(SPI1, &SPI_InitStructure); //Настраиваем SPI1
  SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_RXNE,ENABLE); //Включаем прерывание по приему байта
  SPI_Cmd(SPI1, ENABLE); // Включаем модуль SPI1....
  NVIC_EnableIRQ(SPI1_IRQn); //Разрешаем прерывания от SPI1
	
	
}
    
 
    
 
 
 
int main(void) {
    //Initialize system
    SystemInit(); 
	
//    //Initialize ILI9341
//    TM_ILI9341_Init();
//    //Rotate LCD for 90 degrees
//    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
//    //FIll lcd with color
//    TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
//	
	 TM_SPI_Init1();
	
 
	/*///////////////////
       SPI PROGRAMM
  *///////////////////


    /* Initialize SPI */
    /* SCK = PA5, MOSI = PA7, MISO = PA6 */
 
		/*///////////////////
         DISPLAY
  *///////////////////
//    //Draw white circle
//    TM_ILI9341_DrawCircle(60, 60, 40, ILI9341_COLOR_GREEN);
//    //Draw red filled circle
//    TM_ILI9341_DrawFilledCircle(60, 60, 35, ILI9341_COLOR_RED);
//    //Draw blue rectangle
//    TM_ILI9341_DrawRectangle(120, 20, 220, 100, ILI9341_COLOR_BLUE);
//    //Draw black filled rectangle
//    TM_ILI9341_DrawFilledRectangle(130, 30, 210, 90, ILI9341_COLOR_BLACK);
//    //Draw line with custom color 0x0005
//    TM_ILI9341_DrawLine(10, 120, 310, 120, 0x0005);
    
//    //Put string with black foreground color and blue background with 11x18px font
//    TM_ILI9341_Puts(65, 130, "STM32F4 Discovery", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
//    //Put string with black foreground color and blue background with 11x18px font
//    TM_ILI9341_Puts(60, 150, "ILI9341 LCD Module", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
//    //Put string with black foreground color and red background with 11x18px font
//    TM_ILI9341_Puts(150, 150, "priveeet", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
//    	 GPIO_ToggleBits(GPIOG,  GPIO_Pin_13);
    while (1) {
//					GPIO_SetBits(GPIOG,GPIO_Pin_13);
//			 for( gj=0;gj<1000000;gj++){}
//			GPIO_ResetBits(GPIOG, GPIO_Pin_13);
//			 for( gj=0;gj<1000000;gj++){}
//			GPIO_ResetBits(GPIOG, GPIO_Pin_13 | GPIO_Pin_14);
//         /* Send 0x15 over SPI1 */
//			GPIO_ResetBits(GPIOA,GPIO_Pin_4); //Подаем сигнал CS слейву
////    TM_SPI_Send(SPI1, 0x15);
//			SPI_I2S_SendData(SPI1, 0x15); //Передаем байт 0x93 через SPI1
//		 for( gj=0;gj<100000;gj++){}
////while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET) //Передатчик занят?
////	;
//GPIO_SetBits(GPIOA,GPIO_Pin_4); //Снимаем сигнал CS
//if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == SET)
//{
//	uint16_t ttr=666;
//}

////		 for( gj=0;gj<10000000;gj++){}
			 
    }
		
}
