#pragma once
#include "pad.h"

void PAD::resetstates()
{
    was_cliced = false;
}
void PAD::init(int x, int y, int SW, int R)
{
    X_pin = x;
    Y_pin = y;
    SW_pin = SW;
    for (int i = 0; i < 100; i++)
    {
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            x1 += HAL_ADC_GetValue(&hadc1)/4; // Tu chciałeś += ?
            ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_1);
            HAL_ADC_Start(&hadc1);
        }

        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            y1 += HAL_ADC_GetValue(&hadc1)/4;
            ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_2);
            HAL_ADC_Start(&hadc1);
        }
        //println("x1 = " + std::to_string(x1) + " y1 = " + std::to_string(y1));
    }
    x1 = x1 / 100;
    y1 = y1 / 100;
    y2 = R; // y2 odpowiada za none (R koła)
}
void PAD::update()
{
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        x = HAL_ADC_GetValue(&hadc1)/4; // Get X value
        ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_1);
        HAL_ADC_Start(&hadc1);
    }

    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        y = HAL_ADC_GetValue(&hadc1)/4; // Get Y value
        ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_2);
        HAL_ADC_Start(&hadc1);
    }
    sw = digitalRead(GPIOA, SW_pin);


    if (sw == 0)
    {
        was_cliced = true;
    }
    //println(std::to_string(lastpostion_));
    position();
}

PAD::DIR PAD::position()
{
    if ((x - x1) * (x - x1) + (y - y1) * (y - y1) < y2)
    {
        return DIR::NONE; //Definicja DIR w pad.h
    }
    if (x >= y && x <= -y + 1023)
    {
        lastpostion_ = LEFT;
        return DIR::LEFT;
    }
    if (x <= y && x >= -y + 1023)
    {
        lastpostion_ = RIGHT;
        return DIR::RIGHT;
    }
    if (x < y && x < -y + 1023)
    {
        lastpostion_ = UP;
        return DIR::UP;
    }
    if (x > y && x > -y + 1023)
    {
        lastpostion_ = DOWN;
        return DIR::DOWN;
    }
}

bool PAD::isclicked()
{
    return sw == 0;
}

bool PAD::wasclicked()
{
    return was_cliced == true;
}
PAD::DIR PAD::lastpostion()
{
    return lastpostion_;
}
