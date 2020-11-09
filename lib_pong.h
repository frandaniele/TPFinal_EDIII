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
void sendPaleta(uint8_t jugador);
void sendPelota(void);
void sendLineas(uint8_t num);

uint8_t menuPong_screen1[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menuPong_screen2[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tEsperando\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\to\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menuPong_screen3[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\too\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menuPong_screen4[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tEsperando\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\tooo\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t paleta_izq[] = "-  _________\t\t\t-\n\r";

uint8_t paleta_cen[] = "-           _________\t\t-\n\r";

uint8_t paleta_der[] = "-\t\t     _________  -\n\r";

uint8_t linea_vacia[] = "-\t\t\t\t-\n\r";

uint8_t pelota_15[] = "-\t\to\t\t-\n\r";

#endif /* LIB_PONG_H_ */
