/*
 * app_ADC.c
 *
 *  Created on: Mar 26, 2018
 *      Author: LEONARDO
 */

#include "app_ADC.h"
#include "fsl_adc16.h"
#include "stdtypedef.h"

/***************************************
 * Private Macros
 ***************************************/

#define APP_ADC_CHANNEL 0u
#define APP_ADC_CHANNEL_GROUP 0u


/***************************************
 * Variables
 ***************************************/

static T_UBYTE ruw_ADCValue = 0u;
static T_UBYTE rub_ConversionInprogressFlag = false;

/***************************************
 * Private Prototypes
 ***************************************/
static void app_ADC_Trigger(void);
static T_UBYTE app_ADC_ConversionCompleted(void);
static T_UWORD app_ADC_GetsValue(void);



void app_ADC_Init(void)
{
	adc16_config_t ls_ADCConfig;

	//Initialize structure with default values
	ADC16_GetDefaultConfig(&ls_ADCConfig);

	//Init ADC Module
	ADC16_Init(ADC0,&ls_ADCConfig);

	//Disable Trigger for Hardware
	ADC16_EnableHardwareTrigger(ADC0,false);//Trigger for software

	//Autocalibration
	(void)ADC16_DoAutoCalibration(ADC0);
}

static void app_ADC_Trigger(void)
{
	adc16_channel_config_t ls_ChannelConfig;

	//Channel Selection
	ls_ChannelConfig.channelNumber = APP_ADC_CHANNEL;

	//Disable interrupt when Conversion is complete
	ls_ChannelConfig.enableInterruptOnConversionCompleted = false;

	//Disable Differential  Conversion
	ls_ChannelConfig.enableDifferentialConversion = false;

	ADC16_SetChannelConfig(ADC0,APP_ADC_CHANNEL_GROUP, &ls_ChannelConfig);


}

static T_UBYTE app_ADC_ConversionCompleted(void)
{
	T_UBYTE lub_Return;

	lub_Return = false;

	//CHECK IF CONVERSION WAS COMPLETED
	if(kADC16_ChannelConversionDoneFlag &
			ADC16_GetChannelStatusFlags(ADC0, APP_ADC_CHANNEL_GROUP))
	{
		lub_Return = true;
	}


	else
	{
		lub_Return = false;
	}

	return lub_Return;
}


static T_UWORD app_ADC_GetsValue(void)
{
	//RETURN LAST CONVERSION VALUE
	return ADC16_GetChannelConversionValue(ADC0, APP_ADC_CHANNEL_GROUP);
}
;


T_UBYTE app_ADC_Task(void)
{
	if(true == rub_ConversionInprogressFlag )
	{
		//Check if conversion was completed

		if(true == app_ADC_ConversionCompleted())
		{
			ruw_ADCValue = app_ADC_GetsValue()/41;
			rub_ConversionInprogressFlag = false;
		}

		else
		{
			//Do nothing
		}
	}

	else
	{ //Triger the ADC Conversion
		app_ADC_Trigger();

		//set Conversion in progress flag
		rub_ConversionInprogressFlag = true;
	}

return ruw_ADCValue;
}


