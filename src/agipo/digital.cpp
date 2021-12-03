#include "agipo/digital.h"

void digitalWrite(GPIO_TypeDef* port, uint16_t  pin, bool state)
{
    HAL_GPIO_WritePin(port, pin, static_cast<GPIO_PinState>(state));
}
bool digitalRead(GPIO_TypeDef* port, uint16_t pin)
{
    return false;
}