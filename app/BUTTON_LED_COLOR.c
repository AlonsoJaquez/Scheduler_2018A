/*
 * BUTTON_LED_COLOR.c
 *
 *  Created on: Mar 22, 2018
 *      Author: Josue
 */

#include <HAL/Input_Config.h>
#include <MAL_/Button_manager.h>

#include "MKL25Z4.h"
#include "stdtypedef.h"

void Input_Config_portb_Button();
void init_leds();

void app_button_led_color_selector(void){

	T_BOOLEAN BotonRed;
	T_BOOLEAN BotonBlue;
	T_BOOLEAN BotonRed_Blue;

	BotonRed=Button_manager_Read_Button(0);
	BotonBlue=Button_manager_Read_Button(1);
	BotonRed_Blue=Button_manager_Read_Button(2);

	if(BotonRed==FALSE){/// && BotonBlue == FALSE && BotonRed_Blue == FALSE){
		//red_on();
		//blue_off();
		GPIOB->PCOR = 1 << 18;
		GPIOD->PSOR = 1 << 1;
	}
	if(BotonBlue == FALSE){
		GPIOD->PCOR = (1 << 1);
		GPIOB->PSOR = 1 << 18;
		}
		if(BotonRed==FALSE && BotonBlue == FALSE && BotonRed_Blue == TRUE){
			blue_on();
			red_off();
			delay_time(100000);
			red_on();
			blue_off();
		}
	}


