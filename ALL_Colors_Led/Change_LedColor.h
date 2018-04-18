/*
 * Change_LedColor.h
 *
 *  Created on: Mar 18, 2018
 *      Author: DAVID MARTINEX
 */

#ifndef CHANGE_LEDCOLOR_H_
#define CHANGE_LEDCOLOR_H_

#include "stdtypes.h"
#include "stdtypedef.h"


#define SLOW_BLINK      (5000000)
#define FAST_BLINK      (1000000)
#define BLINK_DELAY_FAST     FAST_BLINK
#define BLINK_DELAY_SLOW     SLOW_BLINK
#define LED_GREEN_PIN_NUM  ((uint32_t)19U)
#define LED_RED_PIN_NUM    ((uint32_t)18U)
#define LED_BLUE_PIN_NUM   ((uint32_t)1U)

#define PIN4     4U
#define PIN5     5U

#define PORTC_9_GPIO_IN   ((uint32_t)9U)

extern void delay(int);
extern T_UBYTE ReadPin(void);
extern void app_GPIO_Init(void);
extern void Cfc_LedColor_RED(void);
extern void Cfc_LedColor_BLUE(void);
extern void Cfc_LedColor_GREEN(void);

extern void Cfc_PIN4_ON(void);
extern void Cfc_PIN5_ON(void);

extern void Cfc_PIN4(void);
extern void Cfc_PIN5(void);

extern void led_all_colors(void);
extern void init_verde(void);



#endif /* CHANGE_LEDCOLOR_H_ */
