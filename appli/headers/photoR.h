/*
 * photoR.h
 *
 *  Created on: 18 oct. 2021
 *      Author: hugo
 */

#ifndef PHOTOR_H_
#define PHOTOR_H_

typedef enum{
	INTERIOR,
	EXTERIOR
}e_selectPhotoR;

int16_t PHOTO_R_getValue(e_selectPhotoR selectPhotoR);



#endif /* PHOTOR_H_ */
