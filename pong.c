/*
 * pong.c
 *
 *  Created on: 9 nov. 2020
 *      Author: franc
 */

#include "lib_pong.h"

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

void sendMenuPong(void){
	static uint8_t frame = 0;

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina
	sendTope();

	if(frame==0){
		UART_Send(LPC_UART0,menuPong_screen1,sizeof(menuPong_screen1),BLOCKING);
	}
	else if(frame==1){
		UART_Send(LPC_UART0,menuPong_screen2,sizeof(menuPong_screen2),BLOCKING);
	}
	else if(frame==2){
		UART_Send(LPC_UART0,menuPong_screen3,sizeof(menuPong_screen3),BLOCKING);
	}
	else if(frame==3){
		UART_Send(LPC_UART0,menuPong_screen4,sizeof(menuPong_screen4),BLOCKING);
	}
	frame++;
	if(frame==4){frame = 0;}

	sendTope();

	for(uint32_t i=0; i<400000; i++);

	return;
}

void sendPelota(void){

	UART_Send(LPC_UART0,pelota_15,sizeof(pelota_15),BLOCKING);

	return;
}

void sendPaleta(uint8_t posicion){

	if(posicion==0){
		UART_Send(LPC_UART0,paleta_izq,sizeof(paleta_izq),BLOCKING);
	}
	else if(posicion==1){
		UART_Send(LPC_UART0,paleta_cen,sizeof(paleta_cen),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,paleta_der,sizeof(paleta_der),BLOCKING);
	}

	return;
}

void sendLineas(uint8_t num){

	for(uint8_t i = 0; i<num; i++){
		UART_Send(LPC_UART0,linea_vacia,sizeof(linea_vacia),BLOCKING);
	}

	return;
}
