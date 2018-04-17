/*
 * app_PWM.c
 *
 *  Created on: Mar 31, 2018
 *      Author: LEONARDO
 */
#include <stdio.h>
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"
#include "Change_LedColor.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
#include "clock_config.h"
#include "app_PWM.h"
#include "app_ADC.h"
#include "fsl_adc16.h"
#include "stdtypedef.h"
#include "fsl_port.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
static T_UBYTE ruw_dutycycle = 0u;
static T_UBYTE ruw_ADC_Temperature = 0u;
/***************************************
 * Private Prototypes
 ***************************************/

tpm_config_t tpmInfo;
tpm_chnl_pwm_signal_param_t tpmParam;
tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue;
tpm_pwm_level_select_t pwmLevel_low = 0U;

void app_PWM_init(void)
{   /************************************************************************************
 *Initialize TPM2 Channel 0 or LED RED PORTB18
 ************************************************************************************/
	/* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
	CLOCK_SetTpmClock(1U);

	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
	tpmParam.level = pwmLevel_low;
	TPM_GetDefaultConfig(&tpmInfo);

	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASE, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE, kTPM_SystemClock);
	/************************************************************************************
	 *Initialize TPM2 Channel 1 or LED GREEN  PORTB19
	 ************************************************************************************/
	/* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
	CLOCK_SetTpmClock(1U);

	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL_1;
	tpmParam.level = pwmLevel_low;
	TPM_GetDefaultConfig(&tpmInfo);

	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASE, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE, &tpmParam, 1U,  kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE, kTPM_SystemClock);

	/************************************************************************************
	 *Initialize TPM1 Channel 0 or Fan, PORTB0(pin 43)  A0
	 ************************************************************************************/
	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
	tpmParam.level = pwmLevel_low;

	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASE_1, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE_1, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE_1, kTPM_SystemClock);

	/************************************************************************************
	 *Initialize TPM1 Channel 1 or Power Resistor, PORTB1(pin 44)  A1
	 ************************************************************************************/
	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL_1;
	tpmParam.level = pwmLevel_low;

	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASE_1, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE_1, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE_1, kTPM_SystemClock);

}

void app_PWM_deinit(void)
{   /************************************************************************************
 *Deinitialization TPM1
 ************************************************************************************/

	TPM_Deinit(BOARD_TPM_BASE_1);
}
void app_PWM_reinit(void)
{

	  PORT_SetPinMux(PORTB, 0u, kPORT_MuxAlt3);            /* PORTB0 (pin 54) is configured as TPM2_CH1 */
	  PORT_SetPinMux(PORTB, 1u, kPORT_MuxAlt3);            /* PORTB1 (pin 54) is configured as TPM2_CH1 */

	  CLOCK_SetTpmClock(1U);

	/************************************************************************************
	 *Initialize TPM1 Channel 0 or Fan, PORTB0(pin 43)  A0
	 ************************************************************************************/
	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL;
	tpmParam.level = pwmLevel_low;

	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASE_1, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE_1, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE_1, kTPM_SystemClock);

	/************************************************************************************
	 *Initialize TPM1 Channel 1 or Power Resistor, PORTB1(pin 44)  A1
	 ************************************************************************************/
	/* Configure tpm params with frequency 24kHZ */
	tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL_1;
	tpmParam.level = pwmLevel_low;

	TPM_GetDefaultConfig(&tpmInfo);
	/* Initialize TPM module */
	TPM_Init(BOARD_TPM_BASE_1, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE_1, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE_1, kTPM_SystemClock);
}
void app_PWM_Fan(const T_UBYTE percent)

{
	/* Disable channel output before updating the dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

		/* Update PWM duty cycle */
		TPM_UpdatePwmDutycycle(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
				percent);

		/* Start channel output with updated dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);


}


void app_PWM_LedRed(void)
{   ruw_ADC_Temperature = ADC16_GetChannelConversionValue(ADC0, APP_ADC_CHANNEL_GROUP)/41;
	  /************************************************************************************
	 *Enable TPM2 Channel 0 or LED RED PORTB18
	 ************************************************************************************/
	/* Disable channel output before updating the dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

		/* Update PWM duty cycle */
		TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
				ruw_ADC_Temperature );
		/* Start channel output with updated dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);

}

void app_PWM_LedGreen(T_UBYTE ruw_ADC_Temperature )
{
	//ruw_dutycycle = app_ADC_Task();
/************************************************************************************
*Enable TPM2 Channel 1 or LED GREEN PORTB19
************************************************************************************/
/* Disable channel output before updating the dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1,  kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature);
	/* Start channel output with updated dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

}

void app_PWMHandlerGreen()
{   ruw_dutycycle = app_ADC_Task();
	app_PWM_LedGreen(ruw_dutycycle);
}

void app_PWM_Resistor(const T_UBYTE percent)
{
	/* Disable channel output before updating the dutycycle */
			TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

			/* Update PWM duty cycle */
			TPM_UpdatePwmDutycycle(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, kTPM_CenterAlignedPwm,
					percent);
			/* Start channel output with updated dutycycle */
			TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1,(tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

}

/*************************
 * app_PWM_update(void); Not use in this Practice 4
 */
void app_PWM_update(void)
{
	ruw_ADC_Temperature = ADC16_GetChannelConversionValue(ADC0, APP_ADC_CHANNEL_GROUP)/41;

	if(ruw_ADC_Temperature > 60)//Temperature above Safe Max Limit
	{  	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel_low);

	/************************************************************************************
	 *Enable TPM2 Channel 0 LED RED
	 ************************************************************************************/
	/* Disable channel output before updating the dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature );
	/* Start channel output with updated dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);

	/************************************************************************************
	 *Enable TPM1 Channel 0 that is Fan at 50%, Normal Decrease Action
	 ************************************************************************************/
	/* Disable channel output before updating the dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U);

	/* Update PWM duty cycle */
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
			50 );

	/* Start channel output with updated dutycycle */
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);

	}



	if(ruw_ADC_Temperature < 50)
	{   /************************************************************************************
	     TPM2 Channel 0 disable and TPM1 Channel 0 disable
	 ************************************************************************************/

		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel_low);
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel_low);

		/************************************************************************************
		 *Update TPM2 Channel 0
		 ************************************************************************************/

		tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL_1;
		/* Initialize TPM module */

		TPM_SetupPwm(BOARD_TPM_BASE, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

		TPM_StartTimer(BOARD_TPM_BASE, kTPM_SystemClock);


		/* Disable channel output before updating the dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

		/* Update PWM duty cycle */
		TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, kTPM_CenterAlignedPwm,
				ruw_ADC_Temperature);
		/* Start channel output with updated dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);
		/************************************************************************************
		 *Update TPM1 Channel 1
		 ************************************************************************************/
		tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL_1;
		/* Initialize TPM module */

		TPM_SetupPwm(BOARD_TPM_BASE_1, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

		TPM_StartTimer(BOARD_TPM_BASE_1, kTPM_SystemClock);


		/* Disable channel output before updating the dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

		/* Update PWM duty cycle */
		TPM_UpdatePwmDutycycle(BOARD_TPM_BASE_1, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, kTPM_CenterAlignedPwm,
				ruw_ADC_Temperature);
		/* Start channel output with updated dutycycle */
		TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE_1,(tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

	}

	else {//DO NOTHING}
	}
}
