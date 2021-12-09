#pragma once
#include <bitset>
#include "display_interface.h"
#include "agipo/digital.h"
#include "agipo/serial.h"


class DisplayExternal : public DisplayInterface
{
    SPI_HandleTypeDef& spi;
    std::bitset<8> _screen[8];

    const uint8_t MAX7219_TEST = 0x0f;
    const uint8_t MAX7219_BRIGHTNESS = 0x0a;
    const uint8_t MAX7219_SCAN_LIMIT = 0x0b;
    const uint8_t MAX7219_DECODE_MODE = 0x09;
    const uint8_t MAX7219_SHUTDOWN = 0x0C;
public:
    DisplayExternal(SPI_HandleTypeDef& spi) : spi(spi) {}

    void spiTransmit(uint8_t byte)
    {
        HAL_StatusTypeDef status = HAL_SPI_Transmit(&spi, &byte, 1, 100);
        if (status == HAL_StatusTypeDef::HAL_ERROR)
            println("SPI Transmit Error");
    }

    void maxTransfer(uint8_t address, uint8_t byte)
    {
        digitalWrite(GPIOB, GPIO_PIN_6, false);
        spiTransmit(address);
        spiTransmit(byte);
        digitalWrite(GPIOB, GPIO_PIN_6, true);
    }

    void set_pixel(int x, int y, bool state) override;
    bool get_pixel(int x, int y) override;
    void flush() override;
    void init() override;
};
