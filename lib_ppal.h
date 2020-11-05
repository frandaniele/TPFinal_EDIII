/*
 * lib_ppal.h
 *
 *  Created on: 5 nov. 2020
 *      Author: franc
 */

#ifndef LIB_PPAL_H_
#define LIB_PPAL_H_

#define PUERTO0 0
#define PUERTO2 2
#define PinTx (1<<2)
#define PinRx (1<<3)
#define Pin0 (1<<0)
#define Pin1 (1<<1)
#define Pin2 (1<<2)
#define OUTPUT 1
#define INPUT 0
#define Match0 0
#define REdge 0

void confPIN(void);
void confGPIO(void);
void confUART(void);
void confTIMER(uint32_t ticks);
void confADC(void);
void ADCOff(void);

void menuPpal(void);

void sendMenuPpal(uint8_t juego);
void sendTope(void);//dibuja guiones como tope de pantalla

uint8_t menu_screen1[] =
		"-\tLPCArcade\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tElige un juego\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* RacingCars\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t*****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t*****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menu_screen2[] =
		"-\tLPCArcade\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tElige un juego\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tRacingCars\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* Pong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t*****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t*****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menu_screen3[] =
		"-\tLPCArcade\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tElige un juego\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tRacingCars\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* *****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t*****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menu_screen4[] =
		"-\tLPCArcade\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tElige un juego\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tRacingCars\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPong\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t*****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* *****\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t tope[37] = "---------------------------------\n\r";

#endif /* LIB_PPAL_H_ */
