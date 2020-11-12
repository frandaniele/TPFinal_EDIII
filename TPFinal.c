/*
===============================================================================
 Name        : TPFinal.c
 Author      : Daniele Francisco & Gonzalez Julián
 Version     : 1.1.2
 Copyright   :
 Description : Consola de juegos en LPC1769
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "lpc17xx_uart.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_adc.h"

//----------------librerias propias----------------------//
#include "lib_ppal.h"
#include "lib_rc.h"
#include "lib_pong.h"
#include "lib_invaders.h"

//----------------------VARIABLES GENERALES----------------------//
uint8_t ctrl_menu = 1;//se pone a 0 para avanzar en los menus
uint8_t selector = 0;//segun lo medido en el potenciometro se elige un juego
uint8_t juego = 0;//0:RC,1:Pong,2:Invaders,3... variable que no cambia, al contrario de selector

//----------------------VARIABLES Racing Car----------------------//
uint8_t ctrl_lado = 0;//controla en que lado esta el auto
uint32_t dificultadRC = 0;//obtiene un valor segun lo medido en el potenciometro
uint8_t autos = 0;//varaible para saber si se dibujo un auto o no
//array para darle distintas direcciones a los obstaculos
uint8_t direccion_obst[] = {0,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,0,0,1,0,1,0};

//----------------------VARIABLES Pong----------------------//
uint8_t paleta1 = 1;//controlan la posicion de las paletas
uint8_t paleta2 = 1;

//----------------------VARIABLES Invaders----------------------//
uint8_t cont_bala = 0;//contador para saber donde esta el obstaculo
uint8_t lado_navecita = 1;//1 es izq, 2 es centro, 3 es derecha
uint8_t lado_bala = 0;
uint8_t aliens_vivos[3] = {1,2,3};
uint8_t aliens_muertos = 0;
uint8_t disparo = 0;

//----------------------Main program----------------------//
int main(void) {

	SystemInit();

	confPIN();
	confGPIO();
	confUART();

	menuPpal();

//"arranca" el menu del juego elegido
	if(selector==0){//Racing Cars
		menuRC();
		TIM_Cmd(LPC_TIM0, ENABLE);//activo el TIM0 que controla este juego
	}
	else if(selector==1){//Pong
		menuPong();
		TIM_Cmd(LPC_TIM1, ENABLE);//activo el TIM1 que controla este juego
	}
	else if(selector==2){
		menuAlien();
		TIM_Cmd(LPC_TIM3, ENABLE);//activo el TIM3 que controla este juego
	}
	else{

	}

    while(1) {

    }
    return 0;
}

//----------------------Funciones de configuracion de pines y perifericos----------------------//

void confPIN(void){
	PINSEL_CFG_Type PinCfg;

	//Pin 2 puerto 0 como Tx UART0
	PinCfg.Funcnum = PINSEL_FUNC_1;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCfg.Pinnum = 2;
	PinCfg.Portnum = PUERTO0;
	GPIO_SetDir(PUERTO0,PinTx,OUTPUT);
	PINSEL_ConfigPin(&PinCfg);

	//Pin 0 puerto 2 para interrupcion por gpio
	PinCfg.Funcnum = PINSEL_FUNC_0;
	PinCfg.Portnum = PUERTO2;
	PinCfg.Pinnum = 0;
	GPIO_SetDir(PUERTO2,Pin0,INPUT);
	PINSEL_ConfigPin(&PinCfg);

	//Pin 1 puerto 2 para interrupcion por gpio
	PinCfg.Pinnum = 1;
	GPIO_SetDir(PUERTO2,Pin1,INPUT);
	PINSEL_ConfigPin(&PinCfg);

	//Pin 2 puerto 2 para interrupcion por gpio
	PinCfg.Pinnum = 2;
	GPIO_SetDir(PUERTO2,Pin2,INPUT);
	PINSEL_ConfigPin(&PinCfg);

	//Pin 3 puerto 2 para interrupcion por gpio
	PinCfg.Pinnum = 3;
	GPIO_SetDir(PUERTO2,Pin3,INPUT);
	PINSEL_ConfigPin(&PinCfg);

	//Pin 4 puerto 2 para interrupcion por gpio
	PinCfg.Pinnum = 4;
	GPIO_SetDir(PUERTO2,Pin4,INPUT);
	PINSEL_ConfigPin(&PinCfg);

	//p0.23 como AD0.0
	PinCfg.Funcnum = PINSEL_FUNC_1;
	PinCfg.Pinmode = PINSEL_PINMODE_TRISTATE;
	PinCfg.Portnum = PUERTO0;
	PinCfg.Pinnum = 23;
	PINSEL_ConfigPin(&PinCfg);

	return;
}

void confGPIO(void){
	//configuro interrupciones por gpio en p2.0-4

	LPC_GPIOINT->IO2IntEnR |= Pin0;
	LPC_GPIOINT->IO2IntEnR |= Pin1;
	LPC_GPIOINT->IO2IntEnR |= Pin2;
	LPC_GPIOINT->IO2IntEnR |= Pin3;
	LPC_GPIOINT->IO2IntEnR |= Pin4;

	GPIO_ClearInt(PUERTO2, Pin0);
	GPIO_ClearInt(PUERTO2, Pin1);
	GPIO_ClearInt(PUERTO2, Pin2);
	GPIO_ClearInt(PUERTO2, Pin3);
	GPIO_ClearInt(PUERTO2, Pin4);

	NVIC_EnableIRQ(EINT3_IRQn);

	return;
}

void confUART(void){
	UART_CFG_Type UARTCfg;
	UART_FIFO_CFG_Type FIFOCfg;

	//configuro UART0 a baudrate de 19200, 8 databits, 1 stopbit y sin paridad
	UART_ConfigStructInit(&UARTCfg);
	UARTCfg.Baud_rate = 19200;
	UART_Init(LPC_UART0,&UARTCfg);

	//configuracion fifos por defecto
	UART_FIFOConfigStructInit(&FIFOCfg);
	UART_FIFOConfig(LPC_UART0,&FIFOCfg);

	//habilito transmision por uart0
	UART_TxCmd(LPC_UART0, ENABLE);

	return;
}

void confTIMER0(uint32_t ticks){
	TIM_TIMERCFG_Type TIMERCfg;
	TIM_MATCHCFG_Type MATCHCfg;

	//Configuro el prescaler del timer1 segun la dificultad que elija
	TIMERCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIMERCfg.PrescaleValue = ticks;//ticks/25MHz

	//Configuro el Match0 para que cuando TC cuente 1000 veces interrumpa
	//y resetee. Así puedo actualizar la pantalla cada fraccion de segundo, segun la dificultad
	MATCHCfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	MATCHCfg.IntOnMatch = ENABLE;
	MATCHCfg.ResetOnMatch = ENABLE;
	MATCHCfg.StopOnMatch = DISABLE;
	MATCHCfg.MatchChannel = Match0;
	MATCHCfg.MatchValue = 1000;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIMERCfg);
	TIM_ConfigMatch(LPC_TIM0, &MATCHCfg);

	NVIC_EnableIRQ(TIMER0_IRQn);

	return;
}

void confTIMER1(uint32_t ticks){
	TIM_TIMERCFG_Type TIMERCfg;
	TIM_MATCHCFG_Type MATCHCfg;

	//Configuro el prescaler del timer segun lo que elija cuando llamo la funcion menuPong
	TIMERCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIMERCfg.PrescaleValue = ticks;//ticks/25MHz

	//Configuro el Match0 para que cuando TC cuente 1000 veces interrumpa
	//y resetee. Así puedo actualizar la pantalla dependiendo lo que elija en el funcion menu Pong
	MATCHCfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	MATCHCfg.IntOnMatch = ENABLE;
	MATCHCfg.ResetOnMatch = ENABLE;
	MATCHCfg.StopOnMatch = DISABLE;
	MATCHCfg.MatchChannel = Match0;
	MATCHCfg.MatchValue = 1000;

	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &TIMERCfg);
	TIM_ConfigMatch(LPC_TIM1, &MATCHCfg);


	NVIC_EnableIRQ(TIMER1_IRQn);

	return;
}

void confTIMER3(uint32_t ticks){
	TIM_TIMERCFG_Type TIMERCfg;
	TIM_MATCHCFG_Type MATCHCfg;

	//Configuro el prescaler del timer segun lo que elija cuando llamo la funcion menuInvaders
	TIMERCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIMERCfg.PrescaleValue = ticks;//ticks/25MHz

	//Configuro el Match0 para que cuando TC cuente 1000 veces interrumpa
	//y resetee. Así puedo actualizar la pantalla dependiendo lo que elija en el menuInvaders
	MATCHCfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	MATCHCfg.IntOnMatch = ENABLE;
	MATCHCfg.ResetOnMatch = ENABLE;
	MATCHCfg.StopOnMatch = DISABLE;
	MATCHCfg.MatchChannel = Match0;
	MATCHCfg.MatchValue = 1000;

	TIM_Init(LPC_TIM3, TIM_TIMER_MODE, &TIMERCfg);
	TIM_ConfigMatch(LPC_TIM3, &MATCHCfg);

	NVIC_EnableIRQ(TIMER3_IRQn);

	return;
}


void confADC(void){
	//configuro el ADC modo burst para luego elegir juego y dificultad

	LPC_SC->PCONP |= (1<<12);
	LPC_ADC->ADCR |= (1<<21);
	LPC_SC->PCLKSEL0 |= (3<<24);//CCLK/8
	LPC_ADC->ADCR |= (127<<8);//12,5MHz/128
	LPC_ADC->ADCR |= (1<<0);//ch0
	LPC_ADC->ADCR |= (1<<16);//modo burst
	LPC_ADC->ADINTEN = 1;
	NVIC_EnableIRQ(ADC_IRQn);

	return;
}

void ADCOff(void){
	//desactivo el ADC cuando no se usa mas
	NVIC_DisableIRQ(ADC_IRQn);
	LPC_ADC->ADCR &= ~(1<<16);//no burst
	LPC_ADC->ADCR &= ~(1<<21);
	LPC_SC->PCONP &= ~(1<<12);

	return;
}

//----------------------Funciones de servicio de interrupciones----------------------//

void TIMER0_IRQHandler(void){
	//se encarga de actualizar la pantalla y manejar la logica del juego Racing Car

	static uint8_t puntos = 0;
	static uint8_t lado_obst = 0;
	static uint8_t i = 0;
	static uint8_t cont = 0;//controla en donde se dibuja el obstaculo

	if(cont==0){//le da un carril a cada obstaculo de la matriz de direcciones
		lado_obst = direccion_obst[i];
		i++;
		if(i==sizeof(direccion_obst)-1){
			i=0;
		}
	}

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();
//dependiendo la cantidad de frames que pasaron dibuja el obstaculo en donde corresponde
//en su posicion "y", y le agrega pista arriba y debajo
	if(cont==0){
		sendObstaculo(lado_obst);
		sendPista(4);
	}
	else if(cont==1){
		sendPista(1);
		sendObstaculo(lado_obst);
		sendPista(3);
	}
	else if(cont==2){
		sendPista(2);
		sendObstaculo(lado_obst);
		sendPista(2);
	}
	else if(cont==3){
		sendPista(3);
		sendObstaculo(lado_obst);
		sendPista(1);
	}
	else if(cont==4){
		sendPista(4);
		sendObstaculo(lado_obst);
	}

//si el obstaculo esta de mismo lado que auto, game over
//sino dibuja obstaculo y auto en carriles opuestos
	else if(cont==5 || cont==6){
		if(ctrl_lado==lado_obst){
			sendLost();
			while(1);
		}
		else{
			sendPista(5);
			if(cont==5){
				sendAuto_Obst(lado_obst,0);
			}
			else{
				sendAuto_Obst(lado_obst,1);
			}
			autos++;
		}
	}

	cont++;
	if(cont==7){
		cont=0;
		puntos++;
	}//ya se paso el obstaculo y se "genera" otro, se suma 1 punto

	if(autos==0){//si no hubo que dibujar obstaculo al lado de auto viene aca
		sendAuto(ctrl_lado);
	}

	sendTope();

	sendNivel(puntos);//indica puntaje y nivel actuales

	sendTope();

	autos = 0;

	if((puntos+1)%30 == 0){//cada 3 niveles disminuye el timer, por lo que aumenta dificultad
		LPC_TIM0->PR = dificultadRC - (puntos/30)*500;
	}

	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	return;
}

void TIMER1_IRQHandler(void){
	//se encarga de actualizar la pantalla y manejar la logica del juego Pong

	static uint8_t x_pelota = 8;//determina coord x de la pelota
	static uint8_t cont = 5;//sera la coord y de la pelota, comienza en 5:centro
	static uint8_t sentido = 0;//controla el sentido del mov de la pelota
	static uint8_t goles1 = 0;//goles de c/ jugador
	static uint8_t goles2 = 0;

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();

	sendGoles(goles1, goles2);//dibuja puntuacion

	sendTope();

	sendPaleta(paleta1);//dibuja paleta de arriba

	//dependiendo la coord y de la pelota dibuja la cancha
	//y la pelota en su coord x
	if(cont==0){
		sendPelota(x_pelota);
		sendLineas(9);
	}
	else if(cont==1){
		sendLineas(1);
		sendPelota(x_pelota);
		sendLineas(8);
	}
	else if(cont==2){
		sendLineas(2);
		sendPelota(x_pelota);
		sendLineas(7);
	}
	else if(cont==3){
		sendLineas(3);
		sendPelota(x_pelota);
		sendLineas(6);
	}
	else if(cont==4){
		sendLineas(4);
		sendPelota(x_pelota);
		sendLineas(5);
	}
	else if(cont==5){
		sendLineas(5);
		sendPelota(x_pelota);
		sendLineas(4);
	}
	else if(cont==6){
		sendLineas(6);
		sendPelota(x_pelota);
		sendLineas(3);
	}
	else if(cont==7){
		sendLineas(7);
		sendPelota(x_pelota);
		sendLineas(2);
	}
	else if(cont==8){
		sendLineas(8);
		sendPelota(x_pelota);
		sendLineas(1);
	}
	else if(cont==9){
		sendLineas(9);
		sendPelota(x_pelota);
	}

	if(sentido==0){
		cont++;
		if(cont==10){//en este sentido si llega a 10 llega al tope
			//veo si tiene que rebotar o es gol
			if(paleta2 != 1){
				cont = 5;//fue gol, pelota al medio
				goles1++;//suma gol a player1
			}
			sentido = 1;//cambia de sentido
		}
	}
	if(sentido==1){
		cont--;
		if(cont>=255){//en este sentido si baja de 0 llega al tope
			sentido = 0;//cambia sentido
			cont = 0;
			//veo si tiene que rebotar o es gol
			if(paleta1 != 1){
				cont = 5;//fue gol, pelota al medio
				goles2++;//suma gol player2
			}
		}
	}

	sendPaleta(paleta2);//dibuja paleta jug2

	sendTope();

	TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
	return;
}

void TIMER3_IRQHandler(void){
	//se encarga de actualizar la pantalla y manejar la logica del juego Invaders

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendAliens(aliens_vivos);

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
			sendLinea(5);
		}
		//si bala esta de mismo lado que alien, lo destruye
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
			sendLinea(5);
		}
		if ((aliens_vivos[0]+aliens_vivos[1]+aliens_vivos[2])==0) {
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

	TIM_ClearIntPending(LPC_TIM3, TIM_MR0_INT);
	return;
}

void EINT3_IRQHandler(void){
	for(uint32_t i = 0; i<10000;i++);//retardo antirrebote

	//boton "start", para avanzar de menu
	if(LPC_GPIOINT->IO2IntStatR == 1){//p2.0
		ctrl_menu = 0;
		GPIO_ClearInt(PUERTO2, Pin0);
	}

	//dirige el movimiento del auto, paleta1 o navecita a derecha
	else if(LPC_GPIOINT->IO2IntStatR == 2){//p2.1
		if(juego==0){//si es racing cars
			ctrl_lado = 1;//auto a la derecha
		}
		else if(juego==1){//si es pong
			paleta1++;//paleta1 a la derecha
			if(paleta1==3){paleta1 = 2;}
		}
		else if(juego==2){//si es invaders
			lado_navecita += 1;
			if(lado_navecita>=3){
				lado_navecita = 3; // porque estoy en el borde
			}
		}
		GPIO_ClearInt(PUERTO2, Pin1);
	}

	//dirige movimiento auto, paleta1 o navecita a izquierda
	else if(LPC_GPIOINT->IO2IntStatR == 4){//p2.2
		if(juego==0){//si es racing cars
			ctrl_lado = 0;//auto a la izq
		}
		else if(juego==1){//si es pong
			paleta1--;//paleta1 a la izquierda
			if(paleta1>=255){paleta1 = 0;}
		}
		else if(juego==2){//si es invaders
			lado_navecita -= 1;
			if(lado_navecita==0){
				lado_navecita = 1; // porque estoy en el borde
			}
		}
		GPIO_ClearInt(PUERTO2, Pin2);
	}

	//dirige movimiento de paleta 2 a la derecha o la nave dispara
	else if(LPC_GPIOINT->IO2IntStatR == 8){//p2.3
		if (!disparo) {
				disparo = 1;
				lado_bala = lado_navecita;
			}
		paleta2++;//paleta jug2 a la derecha
		if(paleta2==3){paleta2 = 2;}
		GPIO_ClearInt(PUERTO2, Pin3);
	}

	//dirige movimiento de paleta 2 a la izquierda
	else if(LPC_GPIOINT->IO2IntStatR == 16){//p2.4
		paleta2--;//plaeta jug2 a la izquierda
		if(paleta2>=255){paleta2 = 0;}
		GPIO_ClearInt(PUERTO2, Pin4);
	}

	return;
}

void ADC_IRQHandler(){
	//segun valor medido en el potenciometro asigna valores a selector y dificultadRC
	uint32_t adc0_value = 0;

	adc0_value = 0xFFF&((LPC_ADC->ADDR0)>>4);

	if(adc0_value<560){
		dificultadRC = 11000;//dificultad mas facil (mas lenta la interrupcion)
		selector = 0;//juego Racing Car
	}
	else if((adc0_value>=560) && (adc0_value<2048)){
		dificultadRC = 9000;
		selector = 1;//juego Pong
	}
	else if((adc0_value>=2048) && (adc0_value<3536)){
		dificultadRC = 7000;
		selector = 2;//juego invaders
	}
	else{
		dificultadRC = 5000;//dificultad mas dificil (mas rapida la interrupcion)
		selector = 3;
	}

	return;
}

//----------------------Funciones de Menu principal y de los juegos----------------------//

void menuPpal(void){
	//es el menu principal, elijo que juego quiero jugar
	confADC();

	while(ctrl_menu){
		sendMenuPpal(selector);//dibuja el menu
	}

	ADCOff();//apaga adc, no se usa mas

	juego = selector;//cuando se avanzo determina que juego se eligio

	ctrl_menu = 1;//vuelve a "trabar" en el proximo menu

	return;
}

void menuRC(void){
	//menu del juego de autos, elijo la dificultad
	confADC();//vuelvo a prender ADC para la dificultad

	while(ctrl_menu){
		sendMenuRC(dificultadRC);//dibuja menu
	}

	ctrl_menu = 1;

	confTIMER0(dificultadRC);//configura el tim0 segun la dificultad elegida

	ADCOff();

	return;
}

void menuPong(void){

	while(ctrl_menu){
		sendMenuPong();//dibuja menu
	}

	ctrl_menu = 1;

	confTIMER1(5000);//configura el tim1 p/ que interrumpa c/ 0.2 s

	return;
}

void menuAlien(void){

	while(ctrl_menu){
		sendMenuAlien();//dibuja menu
	}

	ctrl_menu = 1;

	confTIMER3(4000);//configura el tim3 p/ que interrumpa c/ 0.16 s

	return;
}

//----------------------Funciones de dibujo generales----------------------//

void sendMenuPpal(uint8_t juego){
	//dibuja el menu principal... segun el selector manejada por adc destaca que juego se elegira

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();

	if(selector == 0){//dependiendo que juego estaria eligiendo muestra el menu
		UART_Send(LPC_UART0,menu_screen1,sizeof(menu_screen1),BLOCKING);
	}
	else if(selector == 1){
		UART_Send(LPC_UART0,menu_screen2,sizeof(menu_screen2),BLOCKING);
	}
	else if(selector == 2){
		UART_Send(LPC_UART0,menu_screen3,sizeof(menu_screen3),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,menu_screen4,sizeof(menu_screen4),BLOCKING);
	}

	sendTope();

	for(uint32_t i=0; i<400000; i++);//retardo para que se estabilice la pantalla

	return;
}

void sendTope(void){
	//dibuja tope con guiones
	UART_Send(LPC_UART0,tope,sizeof(tope),BLOCKING);

	return;
}
