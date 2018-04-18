/*
 * app_TemperatureControl.c
 *
 *  Created on: Apr 1, 2018
 *      Author: LEONARDO
 */

#include "PWM.h"
#include "fsl_adc16.h"
#include "TemperatureControl.h"
#include "stdtypedef.h"
#include "Change_LedColor.h"
#include "board.h"
#include "ADC.h"

#include "RGB_LEDs.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
static T_UWORD ruw_ADC_Temperature = 0u;// read the temperature from the ADC

static T_UBYTE rub_CtrSeconds = 0u;  // Variable for counts the seconds in Danger

const  T_UBYTE cub_TimeDamage = 5u;  //Maximum time which the system could be in Danger
const  T_UBYTE cub_reset = 0u;       //Reset for the seconds in Danger limits
static T_UBYTE rub_FlagSafeMode = 0u;//Flag that active safe mode

const  T_UBYTE cub_SafeMaxLimit    = 60u; // Safe Maximum Limit for start the fan in  Normal Decrease Action
const  T_UBYTE cub_SafeMinLimit    = 40u; // Safe Minimum Limit start the power resistor in Normal Increase Action
const  T_UBYTE cub_HighDangerLimit = 90u; // High Danger Limit for start the fan in  High Decrease Action
const  T_UBYTE cub_LowDangerLimit  = 20u; // Low Danger Limit for start the power resistor in High Increase Action

const  T_UBYTE cub_NormalIncreaseRes  = 50u; // Power resistor at 50%
const  T_UBYTE cub_HighIncreaseRes    = 0u;// Power resistor at 100%
const  T_UBYTE cub_NormalDecreaseFan  = 50u; // Fan at 50%
const  T_UBYTE cub_HighDecreaseFan    = 0u;// Fan at 100%

const  T_UBYTE cub_PWM_OFF            = 100u;// DutyCycle of 0%

static  T_UBYTE sub_FlagNormalMode = 0u;     //Flag that say me if the temperature is in normal mode
static  T_UBYTE sub_FlagNormalDecrease = 0u; //Flag that say me if the temperature is in Normal Decrease Action
static  T_UBYTE sub_FlagHighDecrease = 0u;   //Flag that say me if the temperature is in High Decrease Action
static  T_UBYTE sub_FlagNormalIncrease = 0u; //Flag that say me if the temperature is in Normal Increase Action
static  T_UBYTE sub_FlagHighIncrease = 0u;   //Flag that say me if the temperature is in High Increase Action



static void TempControl_SafeMode  (T_UBYTE flagSafeMode);
static void TempControl_NormalMode(T_UBYTE flagSafeMode);



void TempControl_NormalDecreaseFan()
{
	PWM_Fan(cub_NormalDecreaseFan);

}

void TempControl_HighDecreaseFan()
{
	PWM_Fan(cub_HighDecreaseFan );
}

void TempControl_NormalIncreaseResistor()
{
	PWM_Resistor(cub_NormalIncreaseRes);
}

void TempControl_HighIncreaseResistor()
{
	PWM_Resistor(cub_HighIncreaseRes);
}


///*********************************************
T_UBYTE TempControl_Counter(void)
{   //get temperature from ADC
	ruw_ADC_Temperature = ADC_Task();
	//check that temperature is higher than Safe Maximum Limit
	if (ruw_ADC_Temperature >= cub_SafeMaxLimit)
	{   LED_BLUE_OFF();
	    LED_RED_OFF();
	/***************************************
	        Action in Normal Decrease Fan
	 **************************************/
	//Flag modes
	sub_FlagNormalIncrease = FALSE;
	sub_FlagHighIncrease = FALSE;
	sub_FlagNormalMode = FALSE;
	sub_FlagNormalDecrease = TRUE;
	sub_FlagHighDecrease  = FALSE;




	//"if" for check the temperature is above High Danger Limit
	if(ruw_ADC_Temperature >= cub_HighDangerLimit )
	{

		/*************************************
	         Action in Higher Decrease Fan
		 **************************************/
		//Flag modes
		sub_FlagNormalIncrease = FALSE;
		sub_FlagHighIncrease = FALSE;
		sub_FlagNormalMode = FALSE;
		sub_FlagNormalDecrease = FALSE;
		sub_FlagHighDecrease  = TRUE;



		rub_CtrSeconds ++;//counts the seconds in High Damage Limit

		//"if" for check the time in High Damage Limit
		if(rub_CtrSeconds == cub_TimeDamage)
		{ /******************************
		          Actions in Safe Mode
		 ******************************/
			Cfc_LedColor_RED();
			rub_CtrSeconds = cub_reset;
			rub_FlagSafeMode = TRUE;

			//ALL PINS AS INPUTS
			app_PWM_Fan_OFF();//Turn off the PWM of the FAN channel
  			app_PWM_deinit();//Deinit the PWM
			set_pins_inputs();//All pins as inputs

		}
		else
		{
			//Do nothing
		}
	}
	//"if" for check the temperature is lower than High Danger Limit
	else if(ruw_ADC_Temperature <= cub_HighDangerLimit )
	{   //if you get out Safe mode
		LED_RED_OFF();
		rub_CtrSeconds = cub_reset;
		rub_FlagSafeMode = FALSE;

	}

	else
	{
		//Do nothing
	}
	}
	//check if temperature is range normal
	else if((ruw_ADC_Temperature > cub_SafeMinLimit ) && (ruw_ADC_Temperature < cub_SafeMaxLimit))
	{  //Flags for modes


		sub_FlagNormalIncrease = FALSE;
		sub_FlagHighIncrease = FALSE;
		sub_FlagNormalMode = TRUE;
		sub_FlagNormalDecrease = FALSE;
		sub_FlagHighDecrease  = FALSE;

	}
	//check that temperature is lower than Safe Minimum Limit
	else if (ruw_ADC_Temperature <= cub_SafeMinLimit)
	{ LED_BLUE_OFF();
	LED_RED_OFF();
	/***************************************
	        Action in Normal Increase Power Resistor
	 **************************************/
	//Flags for modes
	sub_FlagNormalIncrease = TRUE;
	sub_FlagHighIncrease = FALSE;
	sub_FlagNormalMode = FALSE;
	sub_FlagNormalDecrease = FALSE;
	sub_FlagHighDecrease  = FALSE;


	//"if" for check the temperature is above High Danger Limit
	if(ruw_ADC_Temperature <= cub_LowDangerLimit )
	{ /*************************************
	          Action in Higher Increase Power Resistor
	 **************************************/

		//Flags for modes
		sub_FlagNormalIncrease = FALSE;
		sub_FlagHighIncrease = TRUE;
		sub_FlagNormalMode = FALSE;
		sub_FlagNormalDecrease = FALSE;
		sub_FlagHighDecrease  = FALSE;


		rub_CtrSeconds ++;//counts the seconds in Low Damage Limit

		//"if" for check the time in Low Damage Limit
		if(rub_CtrSeconds == cub_TimeDamage)
		{ //Actions in Safe Mode
			Cfc_LedColor_BLUE();
			rub_CtrSeconds = cub_reset;
			rub_FlagSafeMode = TRUE;

			//ALL PINS AS INPUTS
			app_PWM_Resistor_OFF();//Turn off the PWM of the FAN channel
			app_PWM_deinit();//Deinit the PWM
			set_pins_inputs();//All pins as inputs

		}
		else
		{
			//Do nothing
		}
	}
	//"if" for check the temperature is higher than Low Danger Limit
	else if(ruw_ADC_Temperature >= cub_LowDangerLimit )
	{   //if you get out Safe mode
		LED_BLUE_OFF();
		rub_CtrSeconds = cub_reset;
		rub_FlagSafeMode = FALSE;

	}

	else
	{
		//Do nothing
	}
	}
	return rub_FlagSafeMode;
}

static void TempControl_SafeMode(T_UBYTE flagSafeMode)
{
	if(flagSafeMode == TRUE)
	{
		ADC_Task();
	}

	else
	{
		//Do nothing
	}
}

static void TempControl_NormalMode(T_UBYTE flagSafeMode)
{
	if(flagSafeMode == FALSE)
	{
		ADC_Task();
	}

	else
	{
		//Do nothing
	}
}


void TempControl_ADC_10Ticks()
{
	TempControl_NormalMode(rub_FlagSafeMode);

}

void TempControl_ADC_200Ticks()
{
	TempControl_SafeMode(rub_FlagSafeMode);

}


void app_PWM_Resistor_OFF()
{
	PWM_Resistor(cub_PWM_OFF);

}
void app_PWM_Fan_OFF()
{
	PWM_Fan(cub_PWM_OFF);
}



void TempControl_IceTemperature()
{
	if (sub_FlagHighIncrease == TRUE)
	{
		TempControl_HighIncreaseResistor();
	}
	else
	{
		//Do nothing
	}
}

void TempControl_ColdTemperature()
{
	if (sub_FlagNormalIncrease == TRUE)
	{

		TempControl_NormalIncreaseResistor();
	}
	else
	{
		//Do nothing
	}
}

void TempControl_NormalTemperature()
{
	if (sub_FlagNormalMode == TRUE)
	{
		 init_pins();
		PWM_reinit();

		app_PWM_Resistor_OFF();
		app_PWM_Fan_OFF();
		Cfc_LedColor_RED();
		Cfc_LedColor_BLUE();
	}
	else
	{
		//Do nothing
	}
}


void TempControl_WarmTemperature()
{
	if (sub_FlagNormalDecrease == TRUE)
	{

		TempControl_NormalDecreaseFan();


	}
	else
	{
		//Do nothing
	}
}

void TempControl_HoTTemperature()
{
	if (sub_FlagHighDecrease == TRUE)
	{

		TempControl_HighDecreaseFan();
	}
	else
	{
		//Do nothing
	}
}




