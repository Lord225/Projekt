#include "agipo/digital.h"

void digitalWrite(GPIO_TypeDef* port, uint16_t  pin, bool state)
{
    HAL_GPIO_WritePin(port, pin, static_cast<GPIO_PinState>(state));
}
bool digitalRead(GPIO_TypeDef* port, uint16_t pin)
{
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PinState::GPIO_PIN_SET;
}