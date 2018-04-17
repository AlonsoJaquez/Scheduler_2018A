
/*
 * Input_Config.c
 *
 *  Created on: Mar 22, 2018
 *      Author: Josue
 */

#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "Input_Config.h"
#include "stdint.h"
#include <drivers_HAL/fsl_clock.h>
#include <drivers_HAL/fsl_port.h>
#include <drivers_HAL/fsl_gpio.h>

extern void Input_Config_portb_Button(void){
	///PORTB Clock Source Enable
	CLOCK_EnableClock(kCLOCK_PortB);
    // SET PINS AS GPIO'S STRUCTURES
	port_pin_config_t  ls_ButtonRed_PinGPIO , ls_ButtonBlue_PinGPIO ,ls_ButtonRed_Blue_PinGPIO;
	// SET AS GPIO
	ls_ButtonRed_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_ButtonBlue_PinGPIO.mux=kPORT_MuxAsGpio;
	ls_ButtonRed_Blue_PinGPIO.mux=kPORT_MuxAsGpio;

	//PIN CONFIGURATION
	PORT_SetPinConfig(PORTB,BUTTON_RED,&ls_ButtonRed_PinGPIO);//BUTTON RESET
	PORT_SetPinConfig(PORTB,BUTTON_BLUE,&ls_ButtonBlue_PinGPIO);//BUTTON ASCENDENT
	PORT_SetPinConfig(PORTB,BUTTON_COLOR_TOGGLE,&ls_ButtonRed_Blue_PinGPIO);//BUTTON DESCENDENT

	//PIN INITIALIZATION
		//Pin Config Structures //Local Variables
		gpio_pin_config_t ls_ButtonRed_PinCfg ,ls_ButtonBlue_PinCfg,ls_ButtonRedBlue_PinCfg;

		/// Pin As Outputs
		ls_ButtonRed_PinCfg.pinDirection=kGPIO_DigitalInput;
		ls_ButtonBlue_PinCfg.pinDirection=kGPIO_DigitalInput;
		ls_ButtonRedBlue_PinCfg.pinDirection=kGPIO_DigitalInput;

		GPIO_PinInit(GPIOB, BUTTON_RED,&ls_ButtonRed_PinCfg);//BUTTON RESET
		GPIO_PinInit(GPIOB, BUTTON_BLUE,&ls_ButtonBlue_PinCfg);// BUTTON ASCENDENT
		GPIO_PinInit(GPIOB, BUTTON_COLOR_TOGGLE,&ls_ButtonRedBlue_PinCfg);// BUTTON DESCENDENT

		///STRUSCTURES FOR INPUT CONFIGURATION
		port_pin_config_t ls_ButtonRed_PortCfg , ls_ButtonBlue_PortCfg,ls_ButtonRedBlue_PortCfg;
		//INPUTS WITH PULL-UPS
		ls_ButtonRed_PortCfg.pullSelect=kPORT_PullUp;
		ls_ButtonBlue_PortCfg.pullSelect=kPORT_PullUp;
		ls_ButtonRedBlue_PortCfg.pullSelect=kPORT_PullUp;

		PORT_SetPinConfig(PORTB,BUTTON_RED,&ls_ButtonRed_PortCfg );
		PORT_SetPinConfig(PORTB,BUTTON_BLUE,&ls_ButtonBlue_PortCfg );
		PORT_SetPinConfig(PORTB,BUTTON_COLOR_TOGGLE,&ls_ButtonRedBlue_PortCfg );

	return;
}
