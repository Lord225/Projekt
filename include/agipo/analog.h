#include "gpio.h"

int analogRead(GPIO_TypeDef* port, uint16_t  pin);

int adc_read(uint32_t channel);

ADC_HandleTypeDef adc;



