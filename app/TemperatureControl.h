/*
 * app_TemperetureControl.h
 *
 *  Created on: Apr 1, 2018
 *      Author: LEONARDO
 */

#ifndef APP_TEMPERATURECONTROL_H_
#define APP_TEMPERATURECONTROL_H_

/*
 * @brief Enable PWM TPM1 CHANNEL 0 at 50%
 *
 * Functions used

    PWM_Fan(cub_NormalDecreaseFan);
 */
extern void TempControl_NormalDrecreaseFan(void);
/*
 * @brief Enable PWM TPM1 CHANNEL 0 at 100%
 *
 * Functions used

   PWM_Fan(cub_HighDecreaseFan );
 */
extern void TempControl_HighDrecreaseFan(void);
/*
 * @brief Enable PWM TPM1 CHANNEL 1 at 50%
 *
 * Functions used

    PWM_Resistor(cub_NormalIncreaseRes);
 */
extern void TempControl_NormalIncreaseResistor(void);
/*
 * @brief Enable PWM TPM1 CHANNEL 1 at 50%
 *
 * Functions used

   PWM_Resistor(cub_HighIncreaseRes);
 */
extern void TempControl_HighIncreaseResistor(void);
/*
 * @brief Update PWM TPM1 CHANNEL 1 at 0%
 *
 * Functions used

  PWM_Resistor(cub_PWM_OFF);
 */
extern void app_PWM_Resistor_OFF(void);
/*
 * @brief Update PWM TPM1 CHANNEL 1 at 0%
 *
 * Functions used

  PWM_FAN(cub_PWM_OFF);
 */
extern void app_PWM_Fan_OFF(void);
/*!
 * @brief  Checks the ADC value and make logical compare of flags
 *
 * @return   rub_FlagSafeMode  Flag that indicate we´re in safe mode
 *  */
extern T_UBYTE TempControl_Counter(void);
/*!
 * @brief  Update the lecture of ADC each 10 Ticks
 *
 *Functions used

 app_TempControl_NormalMode(rub_FlagSafeMode);

  */
extern void TempControl_ADC_10Ticks();
/*!
 * @brief  Update the lecture of ADC each 200 Ticks
 *
 *Functions used

 app_TempControl_SafeMode(rub_FlagSafeMode);

  */
extern void TempControl_ADC_200Ticks();
/*!
 * @brief Read the flag "sub_FlagNormalMode" and if is TRUE,then
 *  Turn off the TPM modules
 *   reinit the PWM
 *   reinit the pins

  */
extern void TempControl_NormalTemperature();
/*!
 * @brief Read the flag "sub_FlagNormalDecrease" and if is TRUE,then
 *
  Functions used
     TempControl_NormalDecreaseFan();
  */
extern void TempControl_WarmTemperature();
/*!
 * @brief Read the flag "sub_FlagHighDecrease" and if is TRUE,then
 *
  Functions used
     TempControl_HighDecreaseFan();
  */
extern void TempControl_HoTTemperature();
/*!
 * @brief Read the flag "sub_FlagNormalIncrease" and if is TRUE,then
 *
  Functions used
     TempControl_NormalIncreaseResistor();
  */
extern void TempControl_ColdTemperature();
/*!
 * @brief Read the flag "sub_FlagHighIncrease" and if is TRUE,then
 *
  Functions used
     TempControl_HighIncreaseResistor();
  */
extern void TempControl_IceTemperature();


#endif /* APP_TEMPERATURECONTROL_H_ */
