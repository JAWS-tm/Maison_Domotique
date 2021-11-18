#include "headers/temperature.h"
#include "stm32f1_adc.h"
#include "math.h"


#define TEMP_ADC ADC_1

#define TEMP_COEFF 19.5 // mV/°C
#define OFFSET_VOLTAGE 450 // mV
#define STAB_SAVES_NB 10

double getStabilisedValue(double newMeasure);

// Vout = Tambiante * Tcoeff + Offset

// Ta = (Vout - Offset) / Tcoeff

// 0 à 4095 => 0 à 5v
// => Vout = (5/4095) * ADC


static double temperature = 0;

double TEMPERATURE_get() {
	if (ADC_is_new_sample_available()){
		int16_t adc =  ADC_getValue(TEMP_ADC);

		int16_t voltage = (int16_t) ((3.3/4095) * adc * 1000); // en mV

		temperature = getStabilisedValue((double)((voltage - OFFSET_VOLTAGE) / TEMP_COEFF));
	}
	return temperature;
}
double getStabilisedValue(double newMeasure) {

	static double lastTemperatures[STAB_SAVES_NB] = {0};
	// Stabilisation des valeurs
	if (fabs(newMeasure - lastTemperatures[0]) > 0.1){
		double lastTemp_copy[STAB_SAVES_NB];
		memcpy(lastTemp_copy, lastTemperatures, sizeof(lastTemperatures));

		double tot = 0;
		for (int i = 0; i < (STAB_SAVES_NB - 1); i++){
			lastTemperatures[i+1] = lastTemp_copy[i];
			tot += lastTemperatures[i+1];
		}

		lastTemperatures[0] = newMeasure;
		tot += newMeasure;

		temperature = tot / STAB_SAVES_NB;
	}

	return temperature;
}
