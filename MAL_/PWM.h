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

#define ADC_CHANNEL_GROUP 0u
#define lub_percentdivisor 41u
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)

/*
 * @brief Enables the TPM1 channels (0,1) and TMP2 channels (0,1)
 *
 * Functions used

    TPM_Init(BOARD_TPM_BASE, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE, kTPM_SystemClock);

 */
extern void PWM_init(void);
/*
 * @brief Disables the TPM2
 *
 * Functions used

	TPM_Deinit(BOARD_TPM_BASE_1);
 */
extern void app_PWM_deinit(void);
/*
 * @brief update the TPM2
 *

	* app_PWM_update(void); Not use in this Practice 4

 */
extern void PWM_update(void);
/*
 * @brief Update TPM2 Channel 1 or LED GREEN PORTB19
 *
 * Functions used

    Disable channel output before updating the dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

    Update PWM duty cycle
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1,  kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature);
	 Start channel output with updated dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

	* @param ruw_ADC_Temperature  lecture of  ADC

 */
extern void PWM_LedGreen(T_UBYTE ruw_ADC_Temperature);
/*
 * @brief Update the PWM LED_GREEN with ADC value
 *
    ruw_dutycycle = ADC_Task();

  Functions used
    Disable channel output before updating the dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

    Update PWM duty cycle
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1,  kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature);
	 Start channel output with updated dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

 */

extern void PWMHandlerGreen();
/*
 * @brief Update the PWM LED_RED with ADC value
 *

  Functions used

    //Disable channel output before updating the dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

   // Update PWM duty cycle
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1,  kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature);
	// Start channel output with updated dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);


 */
extern void PWM_LedRed(void);
/*
 * @brief Update TPM1 Channel 0 or FAN PORTB0
 *
 * Functions used

    Disable channel output before updating the dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

    Update PWM duty cycle
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1,  kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature);
	 Start channel output with updated dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

	* @param percent   percent of PWM

 */
extern void PWM_Fan(const T_UBYTE percent);
/*
 * @brief Update TPM1 Channel 1 or Resistor PORTB1
 *
 * Functions used

    Disable channel output before updating the dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, 0U);

    Update PWM duty cycle
	TPM_UpdatePwmDutycycle(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1,  kTPM_CenterAlignedPwm,
			ruw_ADC_Temperature);
	 Start channel output with updated dutycycle
	TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASE, (tpm_chnl_t)BOARD_TPM_CHANNEL_1, pwmLevel);

	* @param percent   percent of PWM

 */
extern void PWM_Resistor(const T_UBYTE percent);
/*
 * @brief Enable TPM1 and set the port to TMPMs
 *
 * Functions used

    TPM_GetDefaultConfig(&tpmInfo);

	TPM_Init(BOARD_TPM_BASE_1, &tpmInfo);

	TPM_SetupPwm(BOARD_TPM_BASE_1, &tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);

	TPM_StartTimer(BOARD_TPM_BASE_1, kTPM_SystemClock);


 */
extern void PWM_reinit(void);

#endif /* APP_PWM_H_ */
