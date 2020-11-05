/*
 * lib_pong.h
 *
 *  Created on: 5 nov. 2020
 *      Author: franc
 */

#ifndef LIB_PONG_H_
#define LIB_PONG_H_

void menuPong(void);

void sendMenuPong(void);
void sendPaleta(void);
void sendPelota(void);

uint8_t menuPong_screen1[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tSeleccione la\t\t-\n\r"
		"-\tdificultad:\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tFácil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tNormal\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tDifícil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* Muy difícil\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

#endif /* LIB_PONG_H_ */
