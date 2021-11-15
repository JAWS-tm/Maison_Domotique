#include "headers/temperature.h"
#include "stm32f1_adc.h"

#define TEMP_ADC ADC_1

#define TEMP_COEFF 19.5 // mV/°C
#define OFFSET_VOLTAGE 400 // mV

// Vout = Tambiante * Tcoeff + Offset

// Ta = (Vout - Offset) / Tcoeff

// 0 à 4095 => 0 à 5v
// => Vout = (5/4095) * ADC

double TEMPERATURE_get() {
	if (ADC_is_new_sample_available()){
		int16_t adc =  ADC_getValue(TEMP_ADC);

		int16_t voltage = (int16_t) ((3.3/4095) * adc * 1000); // en mV

		return (double)((voltage - OFFSET_VOLTAGE) / TEMP_COEFF);
	}
	return -1;
}
