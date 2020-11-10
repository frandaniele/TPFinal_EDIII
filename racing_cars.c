/*
 * racing_cars.c
 *
 *  Created on: 9 nov. 2020
 *      Author: franc
 */

#include "lib_rc.h"

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
		"-\t    ((/   \\))\t\t-\n\r"
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

void sendMenuRC(uint32_t dificultad){
	//dibuja el menu juego autos... segun variable dificultad manejada por adc destaca que dificultad
	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();

	if(dificultad == 4500){
		UART_Send(LPC_UART0,menuRC_screen1,sizeof(menuRC_screen1),BLOCKING);
	}
	else if(dificultad == 7000){
		UART_Send(LPC_UART0,menuRC_screen2,sizeof(menuRC_screen2),BLOCKING);
	}
	else if(dificultad == 9000){
		UART_Send(LPC_UART0,menuRC_screen3,sizeof(menuRC_screen3),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,menuRC_screen4,sizeof(menuRC_screen4),BLOCKING);
	}

	sendTope();

	for(uint32_t i=0; i<400000; i++);

	return;
}

void sendAuto(uint8_t lado){
	//dibuja el auto en el carril correspondiente
	if(lado==0){
		UART_Send(LPC_UART0,auto_izq,sizeof(auto_izq),BLOCKING);
	}
	else if(lado==1){
		UART_Send(LPC_UART0,auto_der,sizeof(auto_der),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,auto_cen,sizeof(auto_cen),BLOCKING);
	}

	return;
}

void sendPista(uint8_t lineas){
	//dibuja 1 linea de carretera con raya al medio y otra sin
	for(uint8_t i = 0; i<lineas; i++){
		UART_Send(LPC_UART0,no_linea,sizeof(no_linea),BLOCKING);
		UART_Send(LPC_UART0,linea,sizeof(linea),BLOCKING);
	}

	return;
}

void sendObstaculo(uint8_t lado){
	//dibuja obstaculo en el carril correspondiente
	if(lado==0){
		UART_Send(LPC_UART0,obst_izq,sizeof(obst_izq),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,obst_der,sizeof(obst_der),BLOCKING);
	}

	return;
}

void sendAuto_Obst(uint8_t lado, uint8_t momento){
//dibuja caso de auto y obstaculo en misma altura
	if(lado==1 && momento==0){
		UART_Send(LPC_UART0,auto_izq2,sizeof(auto_izq2),BLOCKING);
	}
	else if(lado==0 && momento==0){
		UART_Send(LPC_UART0,auto_der2,sizeof(auto_der2),BLOCKING);
	}
	else if(lado==1 && momento==1){
		UART_Send(LPC_UART0,auto_izq3,sizeof(auto_izq3),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,auto_der3,sizeof(auto_der3),BLOCKING);
	}

	return;
}

void sendLost(void){

	UART_SendByte(LPC_UART0,12);
	sendTope();
	UART_Send(LPC_UART0,lose_screen,sizeof(lose_screen),BLOCKING);
	sendTope();

	return;
}
