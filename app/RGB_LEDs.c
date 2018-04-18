/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */

#include <drivers_HAL/fsl_gpio.h>
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "fsl_port.h"


#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (1000000)
#define BLINK_DELAY     FAST_BLINK

#define GREEN			(19)
#define GREEN_SHIFT		(1 << 19)
#define BLUE			(1)
#define BLUE_SHIFT		(1 << 1)
#define RED				(18)
#define RED_SHIFT		(1 << 18)

#define PIN4				(4)
#define PIN4_SHIFT		(1 << 4)
#define PIN4_low		(0 << 4)

#define PIN5				(5)
#define PIN5_SHIFT		(1 << 5)


#define PIN0				(0)
#define PIN0_SHIFT		(0 << 0)

#define PIN1				(1)
#define PIN1_SHIFT		(0 << 1)


#define PIN4_OFF		(GPIOC->PSOR = PIN4_SHIFT)
#define PIN4_ON			(GPIOC->PCOR = PIN4_SHIFT)
#define PIN4_TOGGLE		(GPIOC->PTOR = PIN4_SHIFT)

#define PIN5_OFF		(GPIOC->PSOR = PIN5_SHIFT)
#define PIN5_ON			(GPIOC->PCOR = PIN5_SHIFT)
#define PIN5_TOGGLE		(GPIOC->PTOR = PIN5_SHIFT)


#define RED_OFF			(GPIOB->PSOR = RED_SHIFT)
#define RED_ON			(GPIOB->PCOR = RED_SHIFT)
#define RED_TOGGLE		(GPIOB->PTOR = RED_SHIFT)

#define GREEN_OFF		(GPIOB->PSOR = GREEN_SHIFT)
#define GREEN_ON		(GPIOB->PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE	(GPIOB->PTOR = GREEN_SHIFT)

#define BLUE_OFF		(GPIOD->PSOR = BLUE_SHIFT)
#define BLUE_ON			(GPIOD->PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE		(GPIOD->PTOR = BLUE_SHIFT)

enum
{
	OFF,
	ON,
	TOGGLING
};

T_UBYTE re_LEDaction = TOGGLING;

void delay_time(int);
void init_leds();
void red_on();
void red_off();
void green_on();
void green_off();
void blue_on();
void blue_off();






void app_rgb_led(void)
{
		red_on();
		delay_time(BLINK_DELAY);	/* Red */
		red_off();
		green_on();
		delay_time(BLINK_DELAY);	/* Green */
		green_off();
		blue_on();
		delay_time(BLINK_DELAY);	/* Blue */
		red_on();
		delay_time(BLINK_DELAY);	/* Blue + Red */
		green_on();
		blue_on();
		delay_time(BLINK_DELAY);	/* Red + Green */
		red_off();
		blue_on();
		delay_time(BLINK_DELAY);	/* Green + Blue */
		red_on();
		delay_time(BLINK_DELAY);	/* Green + Blue + Red */
		green_off();
		blue_off();
}

void app_rgb_led_fsm(void)
{
	static unsigned char rgb_state = 0;

	if(re_LEDaction == OFF)
	{
		/* All off */
		red_off();
		green_off();
		blue_off();
	}
	else if(re_LEDaction == ON)
	{
		/* White is LED ON */
		red_on();
		green_on();
		blue_on();
	}
	else if(re_LEDaction == TOGGLING)
	{
		/* Toggling LED color */
		switch(rgb_state)
		{
			case 0: /* RESET */
				/* All off */
				red_off();
				green_off();
				blue_off();
				rgb_state = 1;
				break;
			case 1: /* red on */
				red_on();
				green_off();
				blue_off();
				rgb_state = 2;
				break;
			case 2: /* green on */
				red_off();
				green_on();
				blue_off();
				rgb_state = 3;
				break;
			case 3: /* blue on */
				red_off();
				green_off();
				blue_on();
				rgb_state = 4;
				break;
			case 4: /* red + green */
				red_on();
				green_on();
				blue_off();
				rgb_state = 5;
				break;
			case 5: /* red + blue */
				red_on();
				green_off();
				blue_on();
				rgb_state = 6;
				break;
			case 6: /* green + blue */
				red_off();
				green_on();
				blue_on();
				rgb_state = 7;
				break;
			case 7: /* All on */
				red_on();
				green_on();
				blue_on();
				rgb_state = 1;
				break;
			default:
				/* Go to RESET */
				rgb_state = 0;
				break;
		}
	}
	else
	{
		/* Permanent RED means an error! */
		red_on();
		green_off();
		blue_off();
	}
}

void pin4_on(){
	PIN4_ON;
}

void pin4_off()
{
	PIN4_OFF;

}

void pin5_on(){
	PIN5_ON;
}

void pin5_off()
{
	PIN5_OFF;

}


void red_on(){
	RED_ON;
}

void red_off(){
	RED_OFF;
}

void green_on(){
	GREEN_ON;
}

void green_off(){
	GREEN_OFF;
}

void blue_on(){
	BLUE_ON;
}

void blue_off(){
	BLUE_OFF;
}

/********************************************************************/

void delay_time(int number)
{
  volatile int cnt;
  for(cnt=0;cnt<number;cnt++);
}
/********************************************************************/

/********************************************************************/
/*	init_leds()
 * initialize the ports for LEDs
 * ******************************************************************/
void set_pins_inputs(void)
{
	 PORT_SetPinMux(PORTB,0u, kPORT_MuxAsGpio);            /* PORTB0 (pin 54) is configured as TPM2_CH1 */
	 PORT_SetPinMux(PORTB,1u, kPORT_MuxAsGpio);            /* PORTB1 (pin 54) is configured as TPM2_CH1 */
	 PORT_SetPinMux(PORTC,4u, kPORT_MuxAsGpio);            /* PORTB1 (pin 54) is configured as TPM2_CH1 */


	//B0 CHANNEL PWM FAN INPUT

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;


	PORTB->PCR[0] = PORT_PCR_MUX(1);

    // Set the initial output state to low
	GPIOB->PSOR |= PIN0_SHIFT;

	// Set the pins direction to inputs
	GPIOB->PDDR |= PIN0_SHIFT;


	//B0 CHANNEL PWM RESISTOR INPUT

		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;


		PORTB->PCR[1] = PORT_PCR_MUX(1);

	    // Set the initial output state to low
		GPIOB->PSOR |= PIN1_SHIFT;

		// Set the pins direction to inputs
		GPIOB->PDDR |= PIN1_SHIFT;



		SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;


		PORTC->PCR[4] = PORT_PCR_MUX(1);


		GPIOC->PSOR |= PIN4_low;


		GPIOC->PDDR |= PIN4_low;
}


void init_pins(void)
 {


			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;


			PORTC->PCR[4] = PORT_PCR_MUX(1);


			GPIOC->PSOR |= PIN4_low;


			GPIOC->PDDR |= PIN4_SHIFT;


    /*
	 * Initialize the Red LED (PTB18)


		 Turn on clock to PortB module
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

    Set the PTB18 pin multiplexer to GPIO mode
		PORTB->PCR[18] = PORT_PCR_MUX(1);

		 Set the initial output state to high
		GPIOB->PSOR |= RED_SHIFT;

		 Set the pins direction to output
		GPIOB->PDDR |= RED_SHIFT;



	 * Initialize the Green LED (PTB19)


		 Turn on clock to PortB module
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

		Set the PTB19 pin multiplexer to GPIO mode
		PORTB->PCR[19] = PORT_PCR_MUX(1);

		 Set the initial output state to high
		GPIOB->PSOR |= GREEN_SHIFT;

         Set the pins direction to output
		GPIOB->PDDR |= GREEN_SHIFT;  */



	/*
	 * Initialize the Blue LED (PTD1)


		Turn on clock to PortB module
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

		Set the PTD1 pin multiplexer to GPIO mode
		PORTD->PCR[1]= PORT_PCR_MUX(1);

		Set the initial output state to high
		GPIOD->PSOR = BLUE_SHIFT;

		 Set the pins direction to output
		GPIOD->PDDR |= BLUE_SHIFT;*/
}


