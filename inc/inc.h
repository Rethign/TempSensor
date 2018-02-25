#ifndef INC_H
#define INC_H

#include "stm_inc.h"
#include <stdio.h>

#define BUFF_SIZE 64

typedef enum{
	false = 0,
	true = 1

} bool;

extern char UARTBuffer[BUFF_SIZE];

#endif
