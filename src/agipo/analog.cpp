#include "agipo/analog.h"

int analogRead(uint32_t channel)
{
	ADC_ChannelConfTypeDef adc_ch;
	adc_ch.Channel = channel;
	adc_ch.Rank = ADC_REGULAR_RANK_1;
	adc_ch.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
	HAL_ADC_ConfigChannel(&adc, &adc_ch);
 
	HAL_ADC_Start(&adc);
	HAL_ADC_PollForConversion(&adc, 1000);
    return HAL_ADC_GetValue(&adc);
}
/*
int analogRead(GPIO_TypeDef *port, uint16_t pin)
{
    //HAL_ADC_GetValue(port, pin);
    return 0;
}*/