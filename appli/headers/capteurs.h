/*
 * capteurs.h
 *
 *  Created on: 18 oct. 2021
 *      Author: hugo
 */

#ifndef CAPTEURS_H_
#define CAPTEURS_H_

#include "stm32f1xx.h"

void CAPTEURS_init();

bool_e CAPTEUR_up();

bool_e CAPTEUR_down();

#endif /* CAPTEURS_H_ */
