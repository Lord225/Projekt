#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <string>
#include "usart.h"

void print(std::string message, UART_HandleTypeDef& channel = huart2, uint32_t time_out = 100);

void println(std::string message, UART_HandleTypeDef& channel = huart2, uint32_t time_out = 100);
#endif