//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : Evk123
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PD6（SCL）
//              SDA   接PD7（SDA）            
//              ----------------------------------------------------------------
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////?
#include "oled.h"

#include "oledfont.h"  	 

#include "stm32f0xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以选择0x78  0x7A两个地址   默认为0x78

uint8_t OLED[8][128] = { 0 };
uint8_t CMD_Data[] = { 0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6,
		0xA8, 0x3F,

		0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12,

		0xDB, 0x30, 0x8D, 0x14, 0xAF, 0x20, 0x00 };
void WriteCmd(void) {
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, CMD_Data, 29,
			0xff);
}

//向设备写数据
void OLED_Refreash(void) {
	HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, OLED[0], 1024,
			0xff);
}
//初始化oled屏幕
void OLED_Init(void) {
	HAL_Delay(200); //这里的延时很重要
	WriteCmd();
}
//清屏
void OLED_Clear(void) {
	uint8_t i, n;
	for (i = 0; i < 8; i++) {
		for (n = 0; n < 128; n++)
			OLED[i][n] = 0;
	}
}

unsigned int oled_pow(uint8_t m, uint8_t n) {
	unsigned int result = 1;
	while (n--)
		result *= m;
	return result;
}
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x, uint8_t y, unsigned int num, uint8_t len,
		uint8_t size2) {
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++) {
		temp = (num / oled_pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1)) {
			if (temp == 0) {
				OLED_ShowChar(x + (size2 / 2) * t, y, ' ', size2, 0);
				continue;
			} else
				enshow = 1;

		}
		OLED_ShowChar(x + (size2 / 2) * t, y, temp + '0', size2, 0);
	}
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size,
		uint8_t Is_Reverse) {
	unsigned char c = 0, i = 0;
	c = chr - ' '; //得到偏移后的值
	if (x > 128 - 1) {
		x = 0;
		y = y + 2;
	}
	if (Char_Size == 16) {
		if (Is_Reverse == 0) {
			for (i = 0; i < 8; i++) {
				OLED[y][x + i] = F8X16[c * 16 + i];
				OLED[y + 1][x + i] = F8X16[c * 16 + i + 8];
			}
		} else {
			OLED[y][x + i] = ~F8X16[c * 16 + i];
			OLED[y + 1][x + i] = ~F8X16[c * 16 + i + 8];
		}
	}
}

//显示一个字符号串
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size) {
	unsigned char j = 0;
	while (chr[j] != '\0') {
		OLED_ShowChar(x, y, chr[j], Char_Size, 0);
		x += 8;
		if (x > 120) {
			x = 0;
			y += 2;
		}
		j++;
	}
}
//显示汉字
//hzk 用取模软件得出的数组
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no) {
	uint8_t t;

	for (t = 0; t < 16; t++) {
		OLED[y][x + t] = Hzk[2 * no][t];
	}
	for (t = 0; t < 16; t++) {
		OLED[y + 1][x + t] = Hzk[2 * no + 1][t];
	}
}
