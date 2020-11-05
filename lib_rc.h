/*
 * lib_rc.h
 *
 *  Created on: 5 nov. 2020
 *      Author: franc
 */

#ifndef LIB_RC_H_
#define LIB_RC_H_

void menuRC(void);

void sendMenuRC(uint32_t dificultad);
void sendAuto(uint8_t lado);//funcion para dibujar el auto
void sendObstaculo(uint8_t lado);//funcion para dibujar obstaculo
void sendAuto_Obst(uint8_t lado, uint8_t momento);
void sendPista(uint8_t lineas);//funcion para dibujar lineas de pista
void sendLost(void);

uint8_t menuRC_screen1[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tRacing Car\t\t-\n\r"
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

uint8_t menuRC_screen2[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tRacing Car\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tSeleccione la\t\t-\n\r"
		"-\tdificultad:\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tFácil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tNormal\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* Difícil\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tMuy difícil\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menuRC_screen3[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tRacing Car\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tSeleccione la\t\t-\n\r"
		"-\tdificultad:\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tFácil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* Normal\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tDifícil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tMuy difícil\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t menuRC_screen4[] =
		"-\tBienvenido a\t\t-\n\r"
		"-\tRacing Car\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tSeleccione la\t\t-\n\r"
		"-\tdificultad:\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t* Fácil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tNormal\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tDifícil\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tMuy difícil\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tPresione para continuar\t-\n\r";

uint8_t lose_screen[] =
		"-\t    PERDISTE!\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t   ..-^~~~^-..\t\t-\n\r"
		"-\t .~           ~.\t-\n\r"
		"-\t(;:           :;)\t-\n\r"
		"-\t (:           :)\t-\n\r"
		"-\t   ':._   _.:'\t\t-\n\r"
		"-\t       | |\t\t-\n\r"
		"-\t     (=====)\t\t-\n\r"
		"-\t       | |\t\t-\n\r"
		"-\t       | |\t\t-\n\r"
		"-\t       | |\t\t-\n\r"
		"-\t    ((/   \))\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\tSigue intentando\t-\n\r";

uint8_t auto_izq[] =
		"-\t--\t \t\t-\n\r"
		"-     o----o\t|\t\t-\n\r"
		"-\t--\t \t\t-\n\r"
		"-     o----o\t|\t\t-\n\r";

uint8_t auto_der[] =
		"-\t\t \t--\t-\n\r"
		"-\t\t|     o----o\t-\n\r"
		"-\t\t \t--\t-\n\r"
		"-\t\t|     o----o\t-\n\r";
//autos con obstaculos en carril opuesto
uint8_t auto_izq2[] =
		"-\t--\t \t00\t-\n\r"
		"-     o----o\t|\t00\t-\n\r"
		"-\t--\t \t\t-\n\r"
		"-     o----o\t|\t\t-\n\r";

uint8_t auto_der2[] =
		"-\t00\t \t--\t-\n\r"
		"-\t00\t|     o----o\t-\n\r"
		"-\t\t \t--\t-\n\r"
		"-\t\t|     o----o\t-\n\r";

uint8_t auto_izq3[] =
		"-\t--\t \t\t-\n\r"
		"-     o----o\t|\t\t-\n\r"
		"-\t--\t \t00\t-\n\r"
		"-     o----o\t|\t00\t-\n\r";

uint8_t auto_der3[] =
		"-\t\t \t--\t-\n\r"
		"-\t\t|     o----o\t-\n\r"
		"-\t00\t \t--\t-\n\r"
		"-\t00\t|     o----o\t-\n\r";

uint8_t auto_cen[]=
		"-\t\t--\t\t-\n\r"
		"-\t      o----o\t\t-\n\r"
		"-\t\t--\t\t-\n\r"
		"-\t      o----o\t\t-\n\r";

uint8_t obst_izq[] =
		"-\t00\t \t\t-\n\r"
		"-\t00\t|\t\t-\n\r";

uint8_t obst_der[] =
		"-\t\t \t00\t-\n\r"
		"-\t\t|\t00\t-\n\r";

uint8_t linea[15] = "-\t\t|\t\t-\n\r";

uint8_t no_linea[16] = "-\t\t \t\t-\n\r";

#endif /* LIB_RC_H_ */
