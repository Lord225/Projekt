#include "agipo/serial.h"

void print(std::string message, UART_HandleTypeDef& channel, uint32_t time_out){
    HAL_UART_Transmit(&channel, (uint8_t *)message.c_str(), message.length(), time_out);
}

void println(std::string message, UART_HandleTypeDef& channel, uint32_t time_out){
    message += '\n';
    print(message, channel, time_out);
}
