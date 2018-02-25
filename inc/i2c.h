/*****************************************************************
 * @title:		comm.h
 * @author: 	Maciej Urda
 * @version:	1.0.0
 * @date:		25-01-2017
 * @brief:		Plik naglowkowy funkcji komunikacyjnych
 * *************************************************************** */

#ifndef I2C_H
#define I2C_H

/* Includes */
#include "inc.h"

/* Defines */
#define ADDRESS_WRITE 0x7E 	/*I2C Slave Write Address*/
#define ADDRESS_READ 0x41	/*I2C Slave Read Address*/

/* Functions */
void Init_I2C(void);
int write_I2C(int data);
int read_I2C(void);

#endif
