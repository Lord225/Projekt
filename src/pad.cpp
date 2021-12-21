#include "pad.h"

    void PAD::buttonreset()
    {   
        was_cliced = false;
    };
    void PAD::set_PAD(int x, int y, int SW, int R)
    {
        X_pin = x;
        Y_pin = y;
        SW_pin = SW;
        for (int i = 0; i < 100; i++)
        {
            if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            x1 = HAL_ADC_GetValue(&hadc1); // Get X value
            ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_1);
            HAL_ADC_Start(&hadc1);
        }

        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            y1 = HAL_ADC_GetValue(&hadc1); // Get Y value
            ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_2);
            HAL_ADC_Start(&hadc1);
        }
          //  x1 += analogRead(0);
          //  y1 += analogRead(1);
        }
        x1 = x1 / 100;
        y1 = y1 / 100;
        y2 = R; // y2 odpowiada za none (R koła)
    };
    void PAD::update()
    {
        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            x = HAL_ADC_GetValue(&hadc1); // Get X value
            ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_1);
            HAL_ADC_Start(&hadc1);
        }

        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            y = HAL_ADC_GetValue(&hadc1); // Get Y value
            ADC_SetActiveChannel(&hadc1, ADC_CHANNEL_2);
            HAL_ADC_Start(&hadc1);
        }
       // x = analogRead(0);
       // y = analogRead(1);
        sw = digitalRead(GPIOA, SW_pin);
        println("Update " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(sw));
    };
    
    int PAD::position()
    {
        /*
        UP - 1
        DOWN - 2 
        LEFT - 3
        RIGTH - 4
        NONE - 0
        */
        if ((x - x1) * (x - x1) + (y - y1) * (y - y1) < y2)
        {
            return 0;
        }
        if (x >= y && x <= -y + 1023)
        {
            return 1;
        }
        if (x <= y && x >= -y + 1023)
        {
            return 2;
        }
        if (x < y && x < -y + 1023)
        {
            return 3;
        }
        if (x > y && x > -y + 1023)
        {
            return 4;
        }
    };

    bool PAD::isclicked()
    {
        return sw;
    };
    bool PAD::wasclicked()
    {
        
    };
