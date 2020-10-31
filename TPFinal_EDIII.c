/*
===============================================================================
 Name        : TPFinal.c
 Author      : Daniele Francisco & Gonzalez Julián
 Version     : 1.1
 Copyright   : 
 Description : Juego de autos para LPC1769
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
void menuRC(void);
//funcion rx para obtener nombre de usuario?

void sendMenuPpal(uint8_t juego);
void sendMenuRC(uint32_t dificultad);
void sendAuto(uint8_t lado);//funcion para dibujar el auto
void sendObstaculo(uint8_t tipo, uint8_t lado);//funcion para dibujar obstaculo
void sendPista(uint8_t lineas);//funcion para dibujar lineas de pista
void sendTope(void);//dibuja guiones como tope de pantalla

uint8_t ctrl_lado = 0;//controla en que lado esta el auto
uint8_t ctrl_menu = 1;//se pone a 0 para avanzar en los menus
uint8_t cambio_lado = 0;//es 1 si el auto tiene que cambiar de carril
uint32_t dificultadRC = 0;//obtiene un valor segun lo medido en el potenciometro
uint8_t selector = 0;//segun lo medido en el potenciometro se elige un juego


//hacer un archivo con estos strings
//para hacer un include aca y optimizar el codigo
uint8_t menu_screen1[] = "1\n\r";

uint8_t menu_screen2[] = "2\n\r";

uint8_t menu_screen3[] = "3\n\r";

uint8_t menu_screen4[] = "4\n\r";

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

uint8_t tope[37] = "---------------------------------\n\r";

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

uint8_t auto_cen[]=
		"-\t\t--\t\t-\n\r"
		"-\t      o----o\t\t-\n\r"
		"-\t\t--\t\t-\n\r"
		"-\t      o----o\t\t-\n\r";

uint8_t linea[15] = "-\t\t|\t\t-\n\r";

uint8_t no_linea[16] = "-\t\t \t\t-\n\r";


int main(void) {

	SystemInit();

	confPIN();
	confGPIO();
	confUART();

	menuPpal();

	if(selector==0){
		menuRC();
	}
	else if(selector==1){

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

	GPIO_ClearInt(PUERTO2, Pin0);
	GPIO_ClearInt(PUERTO2, Pin1);
	GPIO_ClearInt(PUERTO2, Pin2);

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

void confTIMER(uint32_t ticks){
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

	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	//pantalla de transicion cuando se cambia de un carril al otro(auto en el centro)
	if(cambio_lado){
		sendTope();

		sendPista(5);

		sendAuto(1);

		sendTope();

		cambio_lado = 0;
	}
	//si no hay cambio de carril se dibuja el auto en el correspondiente
	else{
		sendTope();

		sendPista(5);

		sendAuto(ctrl_lado);

		sendTope();
	}

	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	return;
}

void EINT3_IRQHandler(void){
	//boton "start", para avanzar de menu
	if(LPC_GPIOINT->IO2IntStatR == 1){
		ctrl_menu = 0;
	}
	//dirige el movimiento del auto entre los carriles
	else if(LPC_GPIOINT->IO2IntStatR == 2){
		if(ctrl_lado==0){
			cambio_lado = 1;
		}
		ctrl_lado = 2;
	}
	else if(LPC_GPIOINT->IO2IntStatR == 4){
		if(ctrl_lado==2){
			cambio_lado = 1;
		}
		ctrl_lado = 0;
	}

	GPIO_ClearInt(PUERTO2, Pin0);
	GPIO_ClearInt(PUERTO2, Pin1);
	GPIO_ClearInt(PUERTO2, Pin2);

	return;
}

void ADC_IRQHandler(){
	//segun valor medido en el potenciometro asigna valores a selector y dificultadRC
	uint32_t adc0_value = 0;

	adc0_value = 0xFFF&((LPC_ADC->ADDR0)>>4);

	if(adc0_value<560){
		dificultadRC = 20000;
		selector = 0;
	}
	else if((adc0_value>=560) && (adc0_value<2048)){
		dificultadRC = 15000;
		selector = 1;
	}
	else if((adc0_value>=2048) && (adc0_value<3536)){
		dificultadRC = 10000;
		selector = 2;
	}
	else{
		dificultadRC = 5000;
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

	confTIMER(dificultadRC);

	ADCOff();

	return;
}

void sendMenuPpal(uint8_t juego){
	//dibuja el menu principal... segun el selector destaca que juego se elegira

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

void sendMenuRC(uint32_t dificultad){
	//dibuja el menu juego autos... segun el selector destaca que dificultad
	UART_SendByte(LPC_UART0,12);//caracter para nueva pagina

	sendTope();

	if(dificultad == 5000){
		UART_Send(LPC_UART0,menuRC_screen1,sizeof(menuRC_screen1),BLOCKING);
	}
	else if(dificultad == 10000){
		UART_Send(LPC_UART0,menuRC_screen2,sizeof(menuRC_screen2),BLOCKING);
	}
	else if(dificultad == 15000){
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
		UART_Send(LPC_UART0,auto_cen,sizeof(auto_cen),BLOCKING);
	}
	else{
		UART_Send(LPC_UART0,auto_der,sizeof(auto_der),BLOCKING);
	}

	return;
}

void sendTope(void){
	//dibuja tope sup e inf de pantalla
	UART_Send(LPC_UART0,tope,sizeof(tope),BLOCKING);

	return;
}

void sendPista(uint8_t lineas){
	//dibuja 1 linea de carretera con raya al medio y otra sin
	for(uint8_t i = 0; i<lineas; i++){
		UART_Send(LPC_UART0,linea,sizeof(linea),BLOCKING);
		UART_Send(LPC_UART0,no_linea,sizeof(no_linea),BLOCKING);
	}

	return;
}
