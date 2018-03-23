/*
 * Button_manager.c
 *
 *  Created on: Mar 22, 2018
 *      Author: Josue
 */

#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "Button_manager.h"
#include "stdint.h"
#include <drivers_HAL/fsl_port.h>
#include <drivers_HAL/fsl_gpio.h>

T_UWORD contadorDebounce=0;

T_BOOLEAN Button_manager_Read_Button(uint32_t boton_pin){
			if(GPIO_ReadPinInput(GPIOB, boton_pin)==FALSE){ //CHECK IF BUTTON IS PRESSED
					if(contadorDebounce>=5000){
						contadorDebounce=0;
						return TRUE;
						}
						else {  		contadorDebounce++;
						return FALSE;
						}
						}
			///return FALSE;
		}
