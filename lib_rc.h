/*
 * lib_rc.h
 *
 *  Created on: 5 nov. 2020
 *      Author: franc
 */

#ifndef LIB_RC_H_
#define LIB_RC_H_

#include "LPC17xx.h"
#include "lpc_types.h"

void menuRC(void);

void sendMenuRC(uint32_t dificultad);
void sendAuto(uint8_t lado);//funcion para dibujar el auto
void sendObstaculo(uint8_t lado);//funcion para dibujar obstaculo
void sendAuto_Obst(uint8_t lado, uint8_t momento);
void sendPista(uint8_t lineas);//funcion para dibujar lineas de pista
void sendLost(void);
void sendTope(void);

#endif /* LIB_RC_H_ */
