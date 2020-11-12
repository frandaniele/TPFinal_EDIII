/*
 * lib_invaders.h
 *
 *  Created on: 5 nov. 2020
 *      Author: jukk
 */

#ifndef LIB_INVADERS_H_
#define LIB_INVADERS_H_

#include "LPC17xx.h"
#include "lpc_types.h"

void sendMenuAlien(void);
void sendNave(uint8_t lado_navecita);
void sendWin(void);
void sendLost(void);
void sendTope(void);
void sendAliens(void);
void sendDisparo(uint8_t lado);
void menuAlien(void);
void SendLinea(uint8_t cantLineas);

#endif /* LIB_INVADERS_H_ */