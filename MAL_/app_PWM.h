/*
 * app_PWM.h
 *
 *  Created on: Mar 31, 2018
 *      Author: LEONARDO
 */

#ifndef APP_PWM_H_
#define APP_PWM_H_

#include "stdtypedef.h"
#define BOARD_TPM_BASE TPM2
#define BOARD_TPM_BASE_1 TPM1
#define BOARD_TPM_CHANNEL 0U
#define BOARD_TPM_CHANNEL_1 1U

#define APP_ADC_CHANNEL_GROUP 0u
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)


extern void app_PWM_init(void);
extern void app_PWM_update(void);
extern void app_PWM_deinit(void);

extern void app_PWM_LedGreen(T_UBYTE ruw_ADC_Temperature);
extern void app_PWMHandlerGreen();
extern void app_PWM_LedRed(void);
extern void app_PWM_Fan(const T_UBYTE percent);
extern void app_PWM_Resistor(const T_UBYTE percent);
extern void app_PWM_reinit(void);

#endif /* APP_PWM_H_ */
