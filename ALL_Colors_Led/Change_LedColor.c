/*
 * Change_LedColor.c
 *
 *  Created on: Mar 18, 2018
 *      Author: David Martinez
 */
#include "stdio.h"
#include "stdtypedef.h"
#include "stdint.h"
#include "Change_LedColor.h"
#include "MKL25Z4.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "board.h"
/*!
 * @brief Led Color.

 */
#define VERDE			(19)
#define VERDE_SHIFT		(1 << 19)

#define VERDE_OFF		(GPIOB->PSOR = VERDE_SHIFT)
#define VERDE_ON		(GPIOB->PCOR = VERDE_SHIFT)
#define VERDE_TOGGLE	(GPIOB->PTOR = VERDE_SHIFT)


#define PIN4			(1)
#define PIN4_SHIFT		(1 << 1)
#define PIN5				(18)
#define PIN5_SHIFT		(1 << 18)




#define PIN4_OFF		 (GPIOB->PSOR = PIN4_SHIFT)
#define PIN4_ON			(GPIOC->PCOR = PIN4_SHIFT)
#define PIN4_TOGGLE		(GPIOC->PTOR = PIN4_SHIFT)

#define PIN5_OFF		(GPIOC->PSOR = PIN5_SHIFT)
#define PIN5_ON		    (GPIOC->PCOR = PIN5_SHIFT)
#define PIN5_TOGGLE  	(GPIOC->PTOR = PIN5_SHIFT)


void delay(int number){
  volatile int cnt;
  for(cnt=0;cnt<number;cnt++);
}

void led_all_colors(void)
{
	        VERDE_ON;
            VERDE_OFF;
	        /*Cfc_LedColor_RED ();
			//delay(BLINK_DELAY_SLOW);
			LED_RED_OFF();

			Cfc_LedColor_BLUE ();
			//delay(BLINK_DELAY_SLOW);
			LED_BLUE_OFF();

			Cfc_LedColor_GREEN ();
			//delay(BLINK_DELAY_SLOW);
			LED_GREEN_OFF();

			//ROJO CON AZUL
			Cfc_LedColor_RED();
			Cfc_LedColor_BLUE ();
			//delay(BLINK_DELAY_SLOW);
			LED_BLUE_OFF();


			//ROJO CON VERDE
			Cfc_LedColor_GREEN ();
			//delay(BLINK_DELAY_SLOW);

			//VERDE CON AZUL
			LED_RED_OFF();
			Cfc_LedColor_BLUE ();
			//delay(BLINK_DELAY_SLOW);

			//VERDE AZUL ROJO
			Cfc_LedColor_RED();
			//delay(BLINK_DELAY_SLOW);

			LED_GREEN_OFF();
			LED_RED_OFF();
			LED_BLUE_OFF();*/


}

T_UBYTE ReadPin()
{
T_UBYTE lub_PinValue;

  lub_PinValue = (T_UBYTE)GPIO_ReadPinInput(GPIOC, PORTC_9_GPIO_IN );


	if(lub_PinValue == TRUE)
	{
		GPIO_ClearPinsOutput(GPIOD,1U << 1U);//led red on
		printf("TRUE");

	}

	else
	{
		GPIO_SetPinsOutput(GPIOD,1U << 1U);//led ren
		printf("False");
	}


	return lub_PinValue;
}

void app_GPIO_Init(void)
{
	//HABILITAR RELOJ C
	CLOCK_EnableClock( kCLOCK_PortC );

	//CONFIGURATION OF PIN AS A GPIO
	port_pin_config_t ls_PinConfig;
	ls_PinConfig.mux = kPORT_MuxAsGpio;

	PORT_SetPinConfig(PORTC,PORTC_9_GPIO_IN,&ls_PinConfig);

	//CONFIGURATION AS A OUTPUT
	gpio_pin_config_t ls_GPIOPinCfg;
	gpio_pin_config_t* lps_GPIOPinCfg;

	lps_GPIOPinCfg = &ls_GPIOPinCfg;

	ls_GPIOPinCfg.pinDirection = kGPIO_DigitalInput;
	ls_GPIOPinCfg.outputLogic = FALSE;


	GPIO_PinInit(GPIOC, PORTC_9_GPIO_IN, lps_GPIOPinCfg);


}

void  Cfc_LedColor_RED (void)
{
	//SET LED GREEN
	//PORTB CLOCK SOURCE ENABLE
	CLOCK_EnableClock( kCLOCK_PortB );

	//pin mux RED
	port_pin_config_t ls_LedREDPinMux;
	ls_LedREDPinMux.mux = kPORT_MuxAsGpio;
	PORT_SetPinConfig(PORTB,LED_RED_PIN_NUM,&ls_LedREDPinMux);


	//LED RED POINTER FOR GPIO THIRD PARAMETER

	gpio_pin_config_t ls_LedRedPinCfg;
	gpio_pin_config_t* lps_LedRedPinCfg;

	lps_LedRedPinCfg = &ls_LedRedPinCfg;

	ls_LedRedPinCfg.pinDirection = kGPIO_DigitalOutput;
	ls_LedRedPinCfg.outputLogic = FALSE;

	//PIN INITIALIZACION
	GPIO_PinInit(GPIOB, LED_RED_PIN_NUM, lps_LedRedPinCfg);

	return;
}

void  Cfc_LedColor_BLUE(void)
{ 	//PORTD CLOCK ENABLE
	CLOCK_EnableClock( kCLOCK_PortD );

	//pin mux Blue
	port_pin_config_t ls_LedBluePinMux;
	ls_LedBluePinMux.mux = kPORT_MuxAsGpio;
	PORT_SetPinConfig(PORTD,LED_BLUE_PIN_NUM,&ls_LedBluePinMux);

	//LED BLUE POINTER FOR GPIO 3 PARAMETER

	gpio_pin_config_t ls_LedBluePinCfg;
	gpio_pin_config_t* lps_LedBluePinCfg;

	lps_LedBluePinCfg = &ls_LedBluePinCfg;

	ls_LedBluePinCfg.pinDirection = kGPIO_DigitalOutput;
	ls_LedBluePinCfg.outputLogic = FALSE;

	//PIN INITIALIZACION
	GPIO_PinInit(GPIOD, LED_BLUE_PIN_NUM, lps_LedBluePinCfg);
}

void  Cfc_LedColor_GREEN(void)
{
	//PORTB CLOCK SOURCE ENABLE
	CLOCK_EnableClock( kCLOCK_PortB );

	//pin mux GREEN
	port_pin_config_t ls_LedGreenPinMux;
	ls_LedGreenPinMux.mux = kPORT_MuxAsGpio;
	PORT_SetPinConfig(PORTB,LED_GREEN_PIN_NUM,&ls_LedGreenPinMux);


	//LED GREEN POINTER FOR GPIO 3 PARAMETER

	gpio_pin_config_t ls_LedGreenPinCfg;
	gpio_pin_config_t *lps_LedGreenPinCfg;

	lps_LedGreenPinCfg = &ls_LedGreenPinCfg;

	ls_LedGreenPinCfg.pinDirection = kGPIO_DigitalOutput;
	ls_LedGreenPinCfg.outputLogic = FALSE;

	//PIN INITIALIZACION
	GPIO_PinInit(GPIOB, LED_GREEN_PIN_NUM, lps_LedGreenPinCfg);


}



void init_verde(void)
{

	/*
	 * Initialize the Green LED (PTB19)
	 */

		/* Turn on clock to PortB module */
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

		/* Set the PTB19 pin multiplexer to GPIO mode */
		PORTB->PCR[19] = PORT_PCR_MUX(1);

		/* Set the initial output state to high */
		GPIOB->PSOR |= VERDE_SHIFT;

		/* Set the pins direction to output */
		GPIOB->PDDR |= VERDE_SHIFT;

}

 void Cfc_PIN4(void)
{
	 //PORTB CLOCK SOURCE ENABLE
	 	CLOCK_EnableClock( kCLOCK_PortC );

	 	//pin mux GREEN
	 	port_pin_config_t ls_Pin4Mux;
	 	ls_Pin4Mux.mux = kPORT_MuxAsGpio;
	 	PORT_SetPinConfig(PORTC,PIN4,&ls_Pin4Mux);


	 	//LED GREEN POINTER FOR GPIO 3 PARAMETER

	 	gpio_pin_config_t ls_PIN4Cfg;
	 	gpio_pin_config_t *lps_PIN4Cfg ;

	 	lps_PIN4Cfg = &ls_PIN4Cfg;

	 	ls_PIN4Cfg.pinDirection = kGPIO_DigitalOutput;
	 	ls_PIN4Cfg.outputLogic = FALSE;

	 	//PIN INITIALIZACION
	 	GPIO_PinInit(GPIOC,PIN4,lps_PIN4Cfg);

}

 void Cfc_PIN4_ON(void)
 {
	 PIN4_OFF;
 }

 void Cfc_PIN5(void)
{
	 //PORTB CLOCK SOURCE ENABLE
	 	CLOCK_EnableClock( kCLOCK_PortC );

	 	//pin mux GREEN
	 	port_pin_config_t ls_Pin5Mux;
	 	ls_Pin5Mux.mux = kPORT_MuxAsGpio;
	 	PORT_SetPinConfig(PORTC,PIN5,&ls_Pin5Mux);


	 	//LED GREEN POINTER FOR GPIO 3 PARAMETER

	 	gpio_pin_config_t ls_PIN5Cfg;
	 	gpio_pin_config_t *lps_PIN5Cfg ;

	 	lps_PIN5Cfg = &ls_PIN5Cfg;

	 	ls_PIN5Cfg.pinDirection = kGPIO_DigitalOutput;
	 	ls_PIN5Cfg.outputLogic = FALSE;

	 	//PIN INITIALIZACION
	 	GPIO_PinInit(GPIOC, PIN5,lps_PIN5Cfg);

}
