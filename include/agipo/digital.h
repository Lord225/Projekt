#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#include "gpio.h"

#define LOW 0
#define HIGH 1

void digitalWrite(GPIO_TypeDef *port, uint16_t pin, bool state);

bool digitalRead(GPIO_TypeDef *port, uint16_t pin);

#endif