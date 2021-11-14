#include "stm32f1_adc.h"
#include "photoR.h"

#define PHOTO_R_INT_ADC ADC_2

#define PHOTO_R_EXT_ADC ADC_3



int16_t PHOTO_R_getValue(e_selectPhotoR selectPhotoR){
	if(selectPhotoR == INTERIOR)
		return ADC_getValue(PHOTO_R_INT_ADC);

	else if(selectPhotoR == EXTERIOR)
		return ADC_getValue(PHOTO_R_EXT_ADC);

	return -1;
}
