/*****************************************************************
 * @title:		lcd.c
 * @author: 	Maciej Urda
 * @version:	1.0.0
 * @date:		25-01-2017
 * @brief:		Plik zawierajacy deklaracje funkcji
 * 				LCD I2C
 * 				WARTOSC I2C:	D7 D6 D5 D4 LED E R/W RS
 * *************************************************************** */

/* Includes*/
#include "lcd.h"

/* *************************************** *
 * @brief:	Funkcja inicjalizujaca sterownik
 * 			LCD
 * 			Wg procedur HD44780
 * *************************************** */
int LCD_Init(){
	int i = 0;
	//opoznienie poczatkowe - po starcie systemu
	Delay_LCD(100);		//100 us

	//zresetowanie linii Data oraz pinow sterujacych
	write_I2C(0x08);

	for(i = 0; i < 3; i++){
		write_I2C(0x0C);	//E + LED
		write_I2C(0x3C);	//D5 D4 LED E
		write_I2C(0x38);	//D5 D4 LED
		Delay_LCD(5000);
	}
	write_I2C(0x0C);	//E + LED
	write_I2C(0x2C);	//D5 LED E
	write_I2C(0x28);	//D LED
	Delay_LCD(100);

	//0x28
	LCD_SendCmd(0x28);	//D5 wysoko
	Delay_LCD(100);

	//0x08
	LCD_SendCmd(0x08);
	Delay_LCD(100);

	//0x01
	LCD_SendCmd(0x01);
	Delay_LCD(3000);

	//0x06
	LCD_SendCmd(0x06);
	Delay_LCD(100);

	//0x0C
	LCD_SendCmd(0x0C);
	Delay_LCD(100);

	return 1;
}

/* *************************************** *
 * @brief:	Funkcja opoznienia, pusta petla
 * *************************************** */
void Delay_LCD(int n){
	int i = 0;
	for(i = 0; i < n*24; i++);
	//zegar 24MHz, 24 = 1us
}
/* *************************************** *
 * @param:	wers is a integer
 * 			odpowiada za wiersz LCD
 * @param:	kol is a integer
 * 			odpowiada za kolumne LCD
 * @brief:	Funkcja przesuwajaca kursor
 * 			na odpowiednia pozycje
 * *************************************** */
void LCD_GoTo(int wers, int kol){
	uint8_t pos = 0;
	pos = (wers * 0x40) + kol;
	pos += 0x80;
	LCD_SendCmd(pos);
}
/* *************************************** *
 * @brief:	Wyczyszczenie wyswietlacza LCD
 * *************************************** */
void LCD_Clear(void){
	LCD_SendCmd(0x01);
}
/* *************************************** *
 * @param:	cmd is a integer
 * @brief:	Funkcja przekazujaca komende do
 * 			LCD
 * *************************************** */
void LCD_SendCmd(const char cmd){
	LCD_SendByte(cmd, 0);
}
/* *************************************** *
 * @param:	data is a integer
 * @brief:	Funkcja przekazujaca dane do LCD
 * *************************************** */
void LCD_SendData(const char data){

	LCD_SendByte(data, 1);
}
/* *************************************** *
 * @param:	text is character pointer
 * @brief:	Funkcja przekazujaca tablice
 * 			do LCD
 * *************************************** */
void LCD_SendText( char *text){

	while(*text)
	{
		LCD_SendData(*text);
		text++;
	}
}

/* *************************************** *
 * @param:	cmd is constant character/
 * 			dane do wyslania LCD
 * @param:	func is integer
 * 			ustawienie pinu RS (kom czy dane)
 * @brief:	Funkcja wysylajaca bajt do LCD
 * *************************************** */
void LCD_SendByte(const char cmd, int func){
	int tcmd;
	int tfunc;
	//ustalamy pin RS
	write_I2C(func | 0x08);

	//RS + E + LED
	tfunc = 0x0C | func;
	write_I2C(tfunc);

	//Dane + RS + E + LED
	tcmd = cmd & 0xF0;		//starsza czesc bitow
	write_I2C(tcmd | tfunc);

	//Dane + RS + LED
	write_I2C(tcmd | func | 0x08);

	//RS + LED
	write_I2C(func | 0x08);

	//RS + E + LED
	tfunc = 0x0C | func;
	write_I2C(tfunc);

	//Dane + RS + E
	tcmd = cmd & 0x0F;		//mlodsza czesc bitow
	tcmd = tcmd << 4;		//przesuniecie o 4 bity - mlodsze zajmuja sterowniki
	write_I2C(tcmd | tfunc);

	//Dane + RS
	write_I2C(tcmd | func | 0x08);

	Delay_LCD(100);
}
