#ifndef __ANALOG_H__
#define __ANALOG_H__

#include "gpio.h"

//int analogRead(GPIO_TypeDef* port, uint16_t  pin);

int analogRead(uint32_t channel);

#endif