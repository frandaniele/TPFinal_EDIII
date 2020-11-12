/*
 * aliens.c
 *
 *  Created on: 9 nov. 2020
 *      Author: jukk
 */

#include "lib_invaders.h"

uint8_t cont_bala = 0;//contador para saber donde esta el obstaculo
uint8_t lado_navecita = 1;//  // 1 es izq, 2 es centro, 3 es derecha
uint8_t lado_bala = 0;
uint8_t aliens_vivos[3] = {1,2,3};
uint8_t primero = 1;
uint8_t segundo = 1;
uint8_t tercero = 1;
uint8_t aliens_muertos = 0;
uint8_t disparo = 0;

uint8_t navecitacen[] =
				"\t\t/\\r"
			"  \t\t // \\  \r";

uint8_t navecitacder[] =
				"\t\t\t /\\r"
			"  \t\t\t\t// \\  \r";

uint8_t navecitaizq[] =
				"/\\r"
			   "// \\\r";

uint8_t alien[] =
				" | | \r"
				"/\/\ \r";

uint8_t alien2[] =
				" | |  | | \r"
				"/\/\  /\/\ \r";

uint8_t alien3[] =
				" | |  | |  | | \r"
				"/\/\  /\/\ /\/\\r";

uint8_t alien4[] =
				"\t\t | | \r"
				"\t\t/\/\ \r";

uint8_t alien5[] =
				"\t\t | |  | | \r"
				"\t\t/\/\  /\/\ \r";


uint8_t alien6[] =
				"\t\t\t\t | | \r"
				"\t\t\t\t/\/\ \r";

uint8_t alien7[] =
				" | | \t\t | | \r"
				"/\/\ \t\t/\/\ \r";



uint8_t balacen[] =
				"\t\t !! \r";

uint8_t balader[] =
				"\t\t\t\t !! \r";

uint8_t balaizq[] =
				" !! \r";

uint8_t linea[] =
				"\r";

uint8_t menuAlien1[] =
					"\t Bienvenido a Alien \r"
					"-\t\t/\\t\t-\n\r"
					"-\t\t//\\\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"\t Presione para continuar \r";

uint8_t menuAlien2[] =
					"\t Bienvenido a Alien \r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t/\\t\t-\n\r"
					"-\t\t//\\\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"\t Presione para continuar \r";

uint8_t menuAlien3[] =
					"\t Bienvenido a Alien \r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t\t\t-\n\r"
					"-\t\t/\\t\t-\n\r"
					"-\t\t//\\\t\t-\n\r"
					"\t Presione para continuar \r";

uint8_t win_screen[] =
		"\t    GANASTE!\t\t-\n\r"
		"\r"
		"\t  |   |\r"
		"\t  |   |\r"
		"\t  |   |\r"
		"\t-        -\r"
		"\t -     -\r"
		"\t   ---\r";

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

void sendWin(void) {
	//dibuja la pantalla de ganador
	UART_Send(LPC_UART0,win_screen,sizeof(win_screen),BLOCKING);
	return;
}

void sendLost(void){
	//dibuja la pantalla cuando se pierde
	UART_Send(LPC_UART0,lose_screen,sizeof(lose_screen),BLOCKING);
	return;
}

void sendAliens(void) {
	//dibuja los aliens dependiendo de cuantos quedan vivos
	if (alien_vivos[0] == 0) {
		primero=0;
	}
	if (alien_vivos[1] == 0) {
		segundo = 0;
	}
	if (alien_vivos[2] == 0) {
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

void EINT3_IRQHandler(void){
	for(uint32_t i = 0; i<10000;i++);//retardo antirrebote
	// boton disparo
	if (!disparo) {
		if(LPC_GPIOINT->IO2IntStatR == 1){//p2.0
			disparo = 1;
			GPIO_ClearInt(PUERTO2, Pin0);
		}
	}
	//dirige el movimiento de la navecita entre los carriles
	else if(LPC_GPIOINT->IO2IntStatR == 2){ //supongo que este es derecha
		lado_navecita += 1;
		if(lado_navecita>=3){
			lado_navecita = 3; // porque estoy en el borde
		}
		GPIO_ClearInt(PUERTO2, Pin1);
	}
	else if(LPC_GPIOINT->IO2IntStatR == 4){ //supongo que este es izquierda
		lado_navecita -= 1;
		if(lado_navecita==0){
			lado_navecita = 1; // el otro borde
		}
		GPIO_ClearInt(PUERTO2, Pin2);
	}
	return;
}

void sendDisparo(uint8_t lado){
	//dibuja obstaculo en el carril correspondiente
	if(lado_navecita==1){
		lado_bala=1;
		UART_Send(LPC_UART0,balaizq,sizeof(balaizq),BLOCKING);
	}
	else if(lado_navecita==2){
		lado_bala=2;
		UART_Send(LPC_UART0,balacen,sizeof(balacen),BLOCKING);
	}
	else{
		lado_bala=3;
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

void menuAlien(void){

	while(ctrl_menu){
		sendMenuAlien();
	}

	ctrl_menu = 1;

	confTIMER1(5000);

	return;
}

void SendLinea(uint8_t cantLineas) {
	for(uint8_t i=0; i<cantLineas; i++) {
		UART_Send(LPC_UART0,linea,sizeof(linea),BLOCKING);
	}
	return;
}


void TIMER0_IRQHandler(void){
	//se encarga de actualizar la pantalla
	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina
	sendAliens();
	if (disparo) {
		//dependiendo la cantidad de frames que pasaron dibuja la bala en donde corresponde
		if(cont_bala==0){
			sendLinea(4);
			sendDisparo(lado_navecita);
		}
		else if(cont_bala==1){
			sendLinea(3);
			sendDisparo(lado_navecita);
			sendLinea(1);
		}
		else if(cont_bala==2){
			sendLinea(2);
			sendDisparo(lado_navecita);
			sendLinea(2);
		}
		else if(cont_bala==3){
			sendLinea(1);
			sendDisparo(lado_navecita);
			sendLinea(3);
		}
		else if(cont_bala==4){
			sendDisparo(lado_navecita);
		}
		//si el obstaculo esta de mismo lado que alien, lo destruye
		else if(cont_bala==5 || cont_bala==6){
			for(uint8_t i=0; i<sizeof(aliens_vivos); i++) {
				if (aliens_vivos[i] == lado_bala) {
					//BOOM
					aliens_vivos[i] = 0;
				}
				if (aliens_vivos[i] == 0) {
					//BOOM
					aliens_muertos++;
				}
			}
		}
		if (aliens_muertos == 3) {
			// YOU WIN
			UART_SendByte(LPC_UART0,12);//caracter para nueva pagina
			sendWin();
			while(1) {};
		}

		cont_bala++;
		if(cont_bala==7){//ya se paso la bala y se "genera" otro
			cont_bala = 0;
			disparo = 0;
		}
	}
	else {
		sendLinea(5);
	}

	sendNave(lado_navecita);

	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	return;
}

