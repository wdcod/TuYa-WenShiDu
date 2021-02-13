/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
//Display Flag
unsigned char isDisplay=1;
//USART Receive Buffer
unsigned char aRxBuffer;
//ADC Value
uint16_t ADval[3];
//Temperature and Humidity
float Temperature=0,Humidity=0;
//Date and Time Display from (X,Y)
const unsigned char DX=0,DY=0,TX=32,TY=2;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void OLED_Show_Time()
{
	RTC_TimeTypeDef T;
	RTC_DateTypeDef D;
	//Get_RTC_Time
	HAL_RTC_GetTime(&hrtc, &T, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &D, RTC_FORMAT_BIN);
	//Get Internet Time
	if(D.Year==0)
	{
		mcu_get_system_time();
		HAL_RTC_GetTime(&hrtc, &T, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &D, RTC_FORMAT_BIN);
	}
	OLED_ShowNum(DX, DY, D.Year+2000, 4, 16,' ');		//Number of Year
	OLED_ShowCHinese(DX+8*4, DY, 0);					//Year
	OLED_ShowNum(DX+8*4+16*1, DY, D.Month, 2, 16,'0');	//Number of Month
	OLED_ShowCHinese(DX+8*6+16*1, DY, 1); 				//Month
	OLED_ShowNum(DX+8*6+16*2, DY, D.Date, 2, 16,'0');	//Number of Day
	OLED_ShowCHinese(DX+8*8+16*2, DY, 2);				//Day
	OLED_ShowCHinese(DX+8*8+16*3, DY, D.WeekDay+5);		//Week

	OLED_ShowNum(TX+8*0, TY, T.Hours, 2, 16, '0');		//Number of Hours
	OLED_ShowChar(TX+8*2, TY, ':', 16, 0);				//:
	OLED_ShowNum(TX+8*3, TY, T.Minutes, 2, 16, '0');	//Number of Minutes
	OLED_ShowChar(TX+8*5, TY, ':', 16, 0);				//:
	OLED_ShowNum(TX+8*6, TY, T.Seconds, 2, 16, '0');	//Number of Seconds

	//OLED_Refreash();
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	unsigned char perIR=0,isClear=0;
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	MX_RTC_Init();
	MX_TIM17_Init();
	MX_IWDG_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	//OLED init
	OLED_Init();
	OLED_Clear();
	OLED_Refreash();
	//SHT30 Init
	sht30_init();
	//Start TIM17
	LL_TIM_ClearFlag_UPDATE(TIM17);
	LL_TIM_EnableIT_UPDATE(TIM17);
	LL_TIM_EnableCounter(TIM17);
	//Start ADC Calibration
	//HAL_ADCEx_Calibration_Start(&hadc);
	HAL_Delay(200);
	//TUYA WIFI Init
	wifi_protocol_init();
	//Start Serial Interrupt
	HAL_UART_Receive_IT(&huart1,&aRxBuffer,1);
	//Get Internet Time
	mcu_get_system_time();
	//Start DMA cycle transfer
	HAL_ADC_Start_DMA(&hadc, (uint32_t*)ADval, 3);
	while (1)
	{
		//TuYa Wifi service
		wifi_uart_service();
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		perIR=ADval[IRR_Ar];
		//Get SHT30 data
		sht30_sample(&Temperature, &Humidity);
		//Update data
		all_data_update();
		//Determine whether to update the display status
		if(ADval[IRR_Ar]>=220 && perIR<=200)
		{
			isDisplay=!isDisplay;
		}
		//noDisplay and noClear?
		if(!isDisplay)
		{
			if(!isClear)
			{
				//Close OLED
				OLED_Clear();
				OLED_Refreash();
				isClear=1;
			}
			HAL_IWDG_Refresh(&hiwdg);
			//Close MCU_LED
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, SET);
			HAL_Delay(100);
			continue;
		}
		//Flash light
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		//Output percentage brightness
		OLED_ShowString(0, 4, (unsigned char*)"Light:", 16);
		OLED_ShowNum(48, 4, 100-ADval[Light_Ar]/40.96, 2, 16,' ');
		/*
		//Display infrared Or Battery voltage **Only Choose one of them
		OLED_ShowString(48+8*3, 4, (unsigned char*)"IR:", 16);
		OLED_ShowNum(48+8*6, 4, ADval[IRR_Ar], 4, 16,'0');
		 */
		//Display Battery voltage 0.80566mV/Counter
		OLED_ShowString(64+8*1, 4, (unsigned char*)"B:", 16);
		OLED_ShowNum(64+8*3, 4, ADval[BAT_Ar]*0.80566/1000*10.1, 1, 16,'0');
		OLED_ShowChar(64+8*4, 4, '.', 16, 0);
		OLED_ShowNum(64+8*5, 4, (int)(ADval[BAT_Ar]*0.80566/10*10.1)%100, 2, 16,'0');
		OLED_ShowChar(64+8*7, 4, 'V', 16, 0);
		//Display Tempreature
		OLED_ShowString(0, 6, (unsigned char*)"Temp:", 16);
		OLED_ShowNum(5*8, 6, Temperature, 2, 16,' ');
		OLED_ShowString(7*8, 6, (unsigned char*)".", 16);
		OLED_ShowNum(8*8, 6, ((int)(Temperature*10))%10, 1, 16,' ');
		//Display Humidity
		OLED_ShowString(9*8, 6, (unsigned char*)"Humi:", 16);
		OLED_ShowNum(14*8, 6, Humidity, 2, 16,' ');
		//Display time
		OLED_Show_Time();
		//Refresh OLED
		OLED_Refreash();
		//Reset Flag
		isClear=0;
		//Delay 100ms
		HAL_IWDG_Refresh(&hiwdg);
		HAL_Delay(100);
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
	while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
	{
	}
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while(LL_RCC_HSI_IsReady() != 1)
	{

	}
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_HSI14_Enable();

	/* Wait till HSI14 is ready */
	while(LL_RCC_HSI14_IsReady() != 1)
	{

	}
	LL_RCC_HSI14_SetCalibTrimming(16);
	LL_RCC_LSI_Enable();

	/* Wait till LSI is ready */
	while(LL_RCC_LSI_IsReady() != 1)
	{

	}
	LL_PWR_EnableBkUpAccess();
	if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSI)
	{
		LL_RCC_ForceBackupDomainReset();
		LL_RCC_ReleaseBackupDomainReset();
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
	}
	LL_RCC_EnableRTC();
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_12);
	LL_RCC_PLL_Enable();

	/* Wait till PLL is ready */
	while(LL_RCC_PLL_IsReady() != 1)
	{

	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{

	}
	LL_SetSystemCoreClock(48000000);

	/* Update the time base */
	if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
	{
		Error_Handler();
	}
	LL_RCC_HSI14_EnableADCControl();
	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
	LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_SYSCLK);
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	uart_receive_input(aRxBuffer);
	//HAL_UART_Transmit(&huart1, &aRxBuffer, 1, 0xff);
	HAL_UART_Receive_IT(&huart1,&aRxBuffer,1);
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
