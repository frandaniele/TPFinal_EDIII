/*
===============================================================================
 Name        : TPFinal.c
 Author      : Daniele Francisco & Gonzalez Julián
 Version     : 1.1
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
#include "lib_ppal.h"
#include "lib_rc.h"
#include "lib_pong.h"

uint8_t ctrl_lado = 0;//controla en que lado esta el auto
uint8_t ctrl_menu = 1;//se pone a 0 para avanzar en los menus
uint8_t cambio_lado = 0;//es 1 si el auto tiene que cambiar de carril
uint32_t dificultadRC = 0;//obtiene un valor segun lo medido en el potenciometro
uint8_t selector = 0;//segun lo medido en el potenciometro se elige un juego
uint8_t juego = 0;//0:RC,1:Pong,2... variable que no cambia, al contrario de selector
//se usa en eint3handler para los botones que se comparten entre juegos
uint8_t autos = 0;//varaible para saber si se dibujo un auto o no
uint8_t paleta1 = 1;
uint8_t paleta2 = 1;

uint8_t direccion_obst[] = {0,0,1,0,1,1,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,0,0,1,0,1,0};

int main(void) {

	SystemInit();

	confPIN();
	confGPIO();
	confUART();

	menuPpal();

//"arranca" el menu del juego elegido
	if(selector==0){
		menuRC();
	}
	else if(selector==1){
		menuPong();
	}
	else if(selector==2){

	}
	else{

	}

    while(1) {

    }
    return 0 ;
}

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

	//Pin 3 puerto 0 como Rx UART0
	PinCfg.Pinnum = 3;
	GPIO_SetDir(PUERTO0,PinRx,INPUT);
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
	//configuro interrupciones por gpio en p2.0-2

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

	//Configuro el prescaler del timer segun la dificultad que elija
	TIMERCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIMERCfg.PrescaleValue = ticks;//ticks/25MHz

	//Configuro el Match0 para que cuando TC cuente 1000 veces interrumpa
	//y resetee. Así puedo actualizar la pantalla cada 0.8-0.6-0.4-0.2 seg
	MATCHCfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	MATCHCfg.IntOnMatch = ENABLE;
	MATCHCfg.ResetOnMatch = ENABLE;
	MATCHCfg.StopOnMatch = DISABLE;
	MATCHCfg.MatchChannel = Match0;
	MATCHCfg.MatchValue = 1000;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TIMERCfg);
	TIM_ConfigMatch(LPC_TIM0, &MATCHCfg);
	TIM_Cmd(LPC_TIM0, ENABLE);

	NVIC_EnableIRQ(TIMER0_IRQn);

	return;
}

void confTIMER1(uint32_t ticks){
	TIM_TIMERCFG_Type TIMERCfg;
	TIM_MATCHCFG_Type MATCHCfg;

	//Configuro el prescaler del timer segun la dificultad que elija
	TIMERCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	TIMERCfg.PrescaleValue = ticks;//ticks/25MHz

	//Configuro el Match0 para que cuando TC cuente 1000 veces interrumpa
	//y resetee. Así puedo actualizar la pantalla cada 0.8-0.6-0.4-0.2 seg
	MATCHCfg.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	MATCHCfg.IntOnMatch = ENABLE;
	MATCHCfg.ResetOnMatch = ENABLE;
	MATCHCfg.StopOnMatch = DISABLE;
	MATCHCfg.MatchChannel = Match0;
	MATCHCfg.MatchValue = 1000;

	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &TIMERCfg);
	TIM_ConfigMatch(LPC_TIM1, &MATCHCfg);
	TIM_Cmd(LPC_TIM1, ENABLE);

	NVIC_EnableIRQ(TIMER1_IRQn);

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

void TIMER0_IRQHandler(void){
	//se encarga de actualizar la pantalla

	static uint8_t lado_obst = 0;
	static uint8_t i = 0;
	static uint8_t cont = 0;//controla en donde se dibuja el obstaculo

	if(cont==0){
		lado_obst = direccion_obst[i];
		i++;
		if(i==sizeof(direccion_obst)-1){
			i=0;
		}
	}

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();
//dependiendo la cantidad de frames que pasaron dibuja el obstaculo en donde corresponde
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
	if(cont==7){cont=0;}//ya se paso el obstaculo y se "genera" otro

	if(autos==0){//si no hubo que dibujar obstaculo al lado de auto viene aca
		//pantalla de transicion cuando se cambia de un carril al otro(auto en el centro)
		if(cambio_lado){
			sendAuto(1);
			cambio_lado = 0;
		}
		//si no hay cambio de carril se dibuja el auto en el correspondiente
		else{
			sendAuto(ctrl_lado);
		}
	}

	sendTope();

	autos = 0;

	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	return;
}

void TIMER1_IRQHandler(void){
	static uint8_t x_pelota = 0;
	static uint8_t cont = 0;
	static uint8_t sentido = 0;

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();

	sendPaleta(paleta1);

	/*lineas vacias y linea con pelota*/
	if(cont==0){
		sendPelota();
		sendLineas(9);
	}
	else if(cont==1){
		sendLineas(1);
		sendPelota();
		sendLineas(8);
	}
	else if(cont==2){
		sendLineas(2);
		sendPelota();
		sendLineas(7);
	}
	else if(cont==3){
		sendLineas(3);
		sendPelota();
		sendLineas(6);
	}
	else if(cont==4){
		sendLineas(4);
		sendPelota();
		sendLineas(5);
	}
	else if(cont==5){
		sendLineas(5);
		sendPelota();
		sendLineas(4);
	}
	else if(cont==6){
		sendLineas(6);
		sendPelota();
		sendLineas(3);
	}
	else if(cont==7){
		sendLineas(7);
		sendPelota();
		sendLineas(2);
	}
	else if(cont==8){
		sendLineas(8);
		sendPelota();
		sendLineas(1);
	}
	else if(cont==9){
		sendLineas(9);
		sendPelota();
	}

	if(sentido==0){
		cont++;
		if(cont==10){sentido = 1;}
	}
	if(sentido==1){
		cont--;
		if(cont>=255){
			sentido = 0;
			cont = 0;
		}
	}

	sendPaleta(paleta2);

	sendTope();

	TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
	return;
}

void EINT3_IRQHandler(void){
	for(uint32_t i = 0; i<10000;i++);//retardo antirrebote

	//boton "start", para avanzar de menu
	if(LPC_GPIOINT->IO2IntStatR == 1){
		ctrl_menu = 0;
		GPIO_ClearInt(PUERTO2, Pin0);
	}
	//dirige el movimiento del auto entre los carriles
	else if(LPC_GPIOINT->IO2IntStatR == 2){
		if(juego==0){
			if(ctrl_lado==0){//el auto va de un carril al otro y genera la transicion del medio
				cambio_lado = 1;
			}
			ctrl_lado = 1;
		}
		else if(juego==1){
			paleta1++;
			if(paleta1==3){paleta1 = 2;}
		}
		GPIO_ClearInt(PUERTO2, Pin1);
	}
	else if(LPC_GPIOINT->IO2IntStatR == 4){
		if(juego==0){
			if(ctrl_lado==2){
				cambio_lado = 1;
			}
			ctrl_lado = 0;
		}
		else if(juego==1){
			paleta1--;
			if(paleta1>=255){paleta1 = 0;}
		}
		GPIO_ClearInt(PUERTO2, Pin2);
	}
	else if(LPC_GPIOINT->IO2IntStatR == 8){
		paleta2++;
		if(paleta2==3){paleta2 = 2;}
		GPIO_ClearInt(PUERTO2, Pin3);
	}
	else if(LPC_GPIOINT->IO2IntStatR == 16){
		paleta2--;
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
		dificultadRC = 11000;
		selector = 0;
	}
	else if((adc0_value>=560) && (adc0_value<2048)){
		dificultadRC = 9000;
		selector = 1;
	}
	else if((adc0_value>=2048) && (adc0_value<3536)){
		dificultadRC = 7000;
		selector = 2;
	}
	else{
		dificultadRC = 4500;
		selector = 3;
	}

	return;
}

void menuPpal(void){
	//es el menu principal, elijo que juego quiero jugar
	confADC();

	while(ctrl_menu){
		sendMenuPpal(selector);
	}

	juego = selector;

	ctrl_menu = 1;

	ADCOff();

	return;
}

void menuRC(void){
	//menu del juego de autos, elijo la dificultad
	confADC();

	while(ctrl_menu){
		sendMenuRC(dificultadRC);
	}

	ctrl_menu = 1;

	confTIMER0(dificultadRC);

	ADCOff();

	return;
}

void menuPong(void){

	while(ctrl_menu){
		sendMenuPong();
	}

	ctrl_menu = 1;

	confTIMER1(5000);

	return;
}

void sendMenuPpal(uint8_t juego){
	//dibuja el menu principal... segun el selector manejada por adc destaca que juego se elegira

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();

	if(selector == 0){
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

	for(uint32_t i=0; i<400000; i++);

	return;
}

void sendTope(void){
	//dibuja tope sup e inf de pantalla
	UART_Send(LPC_UART0,tope,sizeof(tope),BLOCKING);

	return;
}
