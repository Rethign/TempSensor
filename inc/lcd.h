/*****************************************************************
 * @title:		lcd.h
 * @author: 	Maciej Urda
 * @version:	1.0.0
 * @date:		25-01-2017
 * @brief:		Plik naglowkowy funkcji wyswietlacza LCD
 * *************************************************************** */

#ifndef lcd_h
#define lcd_h

/* Includes */
#include "i2c.h"
#include "inc.h"

/* Functions */
int LCD_Init(void);
void Delay_LCD(int n);
void LCD_GoTo(int wers, int kol);
void LCD_Clear(void);
void LCD_SendCmd(const char cmd);
void LCD_SendData(const char data);
void LCD_SendText(char *text);
void LCD_SendByte(const char cmd, int func);

#endif
