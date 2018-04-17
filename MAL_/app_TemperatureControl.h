/*
 * app_TemperetureControl.h
 *
 *  Created on: Apr 1, 2018
 *      Author: LEONARDO
 */

#ifndef APP_TEMPERATURECONTROL_H_
#define APP_TEMPERATURECONTROL_H_

extern void app_TempControl_NormalDrecreaseFan(void);
extern void app_TempControl_HighDrecreaseFan(void);
extern void app_TempControl_NormalIncreaseResistor(void);
extern void app_TempControl_NormalIncreaseResistor(void);
extern void app_PWM_Resistor_OFF(void);
extern void app_PWM_Fan_OFF(void);

extern T_UBYTE app_TempControl_Counter(void);
extern void app_TempControl_ADC_10Ticks();
extern void app_TempControl_ADC_200Ticks();

extern void app_TempControl_NormalTemperature();
extern void app_TempControl_WarmTemperature();
extern void app_TempControl_HoTTemperature();
extern void app_TempControl_ColdTemperature();
extern void app_TempControl_IceTemperature();

#endif /* APP_TEMPERATURECONTROL_H_ */
