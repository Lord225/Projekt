#pragma once
#include <string>
#include "usart.h"

void print(std::string message, uint32_t time_out = 100)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)message.c_str(), message.length(), time_out);
}

void println(std::string message, uint32_t time_out = 100)
{
    message += '\n';
    print(message, time_out);
}


