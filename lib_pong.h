/*
 * lib_pong.h
 *
 *  Created on: 5 nov. 2020
 *      Author: franc
 */

#ifndef LIB_PONG_H_
#define LIB_PONG_H_

#include "LPC17xx.h"
#include "lpc_types.h"

void menuPong(void);

void sendMenuPong(void);
void sendPaleta(uint8_t jugador);
void sendPelota(uint8_t x_coord);
void sendLineas(uint8_t num);
void sendGoles(uint8_t jug1, uint8_t jug2);
void sendTope(void);



#endif /* LIB_PONG_H_ */
