#include "stm32f1_adc.h"
#include "photoR.h"

#define PHOTO_R_INT_ADC ADC_2

#define PHOTO_R_EXT_ADC ADC_3





uint16_t PHOTO_R_getValue(e_selectPhotoR selectPhotoR){
	if(selectPhotoR == INT){
		return ADC_getValue(PHOTO_R_INT_ADC);
	}
	else if(selectPhotoR == EXT){
			return ADC_getValue(PHOTO_R_EXT_ADC);
		}
}
