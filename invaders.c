/*
 * aliens.c
 *
 *  Created on: 9 nov. 2020
 *      Author: jukk
 */

#include "lib_invaders.h"

uint8_t menuAlien1[] =
		"\t Bienvenido a Alien \n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t /\\\t\t-\n\r"
		"-\t\t//\\\\\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"\t Presione para continuar \n\r";

uint8_t menuAlien2[] =
		"\t Bienvenido a Alien \n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t /\\\t\t-\n\r"
		"-\t\t//\\\\\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"\t Presione para continuar \n\r";

uint8_t menuAlien3[] =
		"\t Bienvenido a Alien \n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t /\\\t\t-\n\r"
		"-\t\t//\\\\\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"-\t\t\t\t-\n\r"
		"\t Presione para continuar \n\r";

uint8_t navecitacen[] =
			"\t\t /\\\n\r"
			"\t\t//\\\\\n\r";

uint8_t navecitader[] =
			"\t\t\t\t /\\\n\r"
			" \t\t\t\t//\\\\  \n\r";

uint8_t navecitaizq[] =
			" /\\\n\r"
			"//\\\\\n\r";

uint8_t alien[] =
			" || \n\r"
			"/\\/\\ \n\r";

uint8_t alien2[] =
			" ||  \t\t   || \n\r"
			"/\\/\\ \t\t /\\/\\ \n\r";

uint8_t alien3[] =
			" || \t\t || \t\t  || \n\r"
			"/\\/\\ \t\t /\\/\\ \t\t /\\/\\\n\r";

uint8_t alien4[] =
			"\t\t || \n\r"
			"\t\t/\\/\\\n\r";

uint8_t alien5[] =
			"\t\t || \t\t || \n\r"
			"\t\t/\\/\\ \t\t /\\/\\ \n\r";

uint8_t alien6[] =
			"\t\t\t\t || \n\r"
			"\t\t\t\t/\\/\\ \n\r";

uint8_t alien7[] =
			" || \t\t\t\t || \n\r"
			"/\\/\\ \t\t\t\t/\\/\\ \n\r";


uint8_t balacen[] = "\t\t !! \n\r";

uint8_t balader[] = "\t\t\t\t !! \n\r";

uint8_t balaizq[] = " !! \n\r";

uint8_t win_screen[] =
		"\t GANASTE!\n\r"
		"\n\r"
		"\t       \n\r"
		"\t  |   |\n\r"
		"\t  |   |\n\r"
		"\t-        -\n\r"
		"\t -     -\n\r"
		"\t   ---\n\r";

uint8_t linea_blanca[] = "\n\r";

void sendAliens(uint8_t aliens[]) {
	//dibuja los aliens dependiendo de cuantos quedan vivos
	uint8_t primero = 1;
	uint8_t segundo = 1;
	uint8_t tercero = 1;

	if (aliens[0] == 0) {
		primero=0;
	}
	if (aliens[1] == 0) {
		segundo = 0;
	}
	if (aliens[2] == 0) {
		tercero = 0;
	}
	if (!primero) {
		if (!segundo) {
			UART_Send(LPC_UART0,alien6,sizeof(alien6),BLOCKING);
		}
		else if (!tercero) {
			UART_Send(LPC_UART0,alien4,sizeof(alien4),BLOCKING);
		}
		else {
			UART_Send(LPC_UART0,alien5,sizeof(alien5),BLOCKING);
		}
	}
	else if (!segundo) {
		if (!primero) {
			UART_Send(LPC_UART0,alien6,sizeof(alien6),BLOCKING);
		}
		else if (!tercero) {
			UART_Send(LPC_UART0,alien,sizeof(alien),BLOCKING);
		}
		else {
			UART_Send(LPC_UART0,alien7,sizeof(alien7),BLOCKING);
		}
	}
	else if (!tercero) {
		if (!primero) {
			UART_Send(LPC_UART0,alien4,sizeof(alien4),BLOCKING);
		}
		else if (!segundo) {
			UART_Send(LPC_UART0,alien,sizeof(alien),BLOCKING);
		}
		else {
			UART_Send(LPC_UART0,alien2,sizeof(alien2),BLOCKING);
		}
	}
	else {
		UART_Send(LPC_UART0,alien3,sizeof(alien3),BLOCKING);
	}
	return;
}


void sendDisparo(uint8_t lado){
	//dibuja obstaculo en el carril correspondiente
	if(lado==1){
		UART_Send(LPC_UART0,balaizq,sizeof(balaizq),BLOCKING);
	}
	else if(lado==2){
		UART_Send(LPC_UART0,balacen,sizeof(balacen),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,balader,sizeof(balader),BLOCKING);
	}

	return;
}

void sendMenuAlien(void){
	static uint8_t frames = 0;

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina
	sendTope();

	if(frames==0){
		UART_Send(LPC_UART0,menuAlien1,sizeof(menuAlien1),BLOCKING);
	}
	else if(frames==1){
		UART_Send(LPC_UART0,menuAlien2,sizeof(menuAlien2),BLOCKING);
	}
	else if(frames==2){
		UART_Send(LPC_UART0,menuAlien3,sizeof(menuAlien3),BLOCKING);
	}
	frames++;
	if(frames==3){frames = 0;}

	sendTope();

	for(uint32_t i=0; i<400000; i++);

	return;
}

void sendWin(void) {
	//dibuja la pantalla de ganador
	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina
	UART_Send(LPC_UART0,win_screen,sizeof(win_screen),BLOCKING);
	return;
}

void sendLinea(uint8_t cantLineas) {
	for(uint8_t i=0; i<cantLineas; i++) {
		UART_Send(LPC_UART0,linea_blanca,sizeof(linea_blanca),BLOCKING);
	}
	return;
}

void sendNave(uint8_t lado_navecita){
	//dibuja la navecita en el carril correspondiente
	if(lado_navecita==1){
		UART_Send(LPC_UART0,navecitaizq,sizeof(navecitaizq),BLOCKING);
	}
	else if(lado_navecita==2){
		UART_Send(LPC_UART0,navecitacen,sizeof(navecitacen),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,navecitader,sizeof(navecitader),BLOCKING);
	}

	return;
}
