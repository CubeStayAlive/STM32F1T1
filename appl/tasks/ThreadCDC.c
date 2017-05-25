/*
 * ThreadCDC.c
 *
 *  Created on: 25.05.2017
 *      Author: manni1user
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdbool.h>
#include "intersect/IntersectCDC.h"

#include "main.h"
#include "usbd_cdc_if.h"

static int counter_step1 = 0;
static int counter_step2 = 0;
static bool is_connected = false;
static bool is_bauded = false;

void ThreadCDC(void const * argument)
{
	bool step1 = true;
	bool step2 = true;

	UNUSED(argument);

	HAL_GPIO_WritePin(USB_FS_Mark_GPIO_Port, USB_FS_Mark_Pin, GPIO_PIN_RESET);

	while(step1)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		vTaskDelay(100);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		vTaskDelay(1200);
		if( ! HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
		{
			step1 = false;
		}
		counter_step1++;
	}

	// activate USB Full Speed Identification
	HAL_GPIO_WritePin(USB_FS_Mark_GPIO_Port, USB_FS_Mark_Pin, GPIO_PIN_SET);

	while(step2)
	{
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		vTaskDelay(700);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		vTaskDelay(300);
		if( is_connected )
		{
			step2 = false;
		}
		counter_step2++;
	}
	while(true)
	{
		int pcount = 1;
		if( is_connected) pcount++;
		if( is_bauded) pcount++;
		for( int i = 0; i < pcount; i++)
		{
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
			vTaskDelay(150);
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
			vTaskDelay(200);
		}
		vTaskDelay(1800);
	}
}

void CBConnect(void)
{
	is_connected = true;
	is_bauded = false;
}
void CBDisconnect(void)
{
	is_connected = false;
	is_bauded = false;
}

void CBBaud(void)
{
	is_bauded = false;
}

static unsigned char answer[] = "Hello\015\012";

void CBIncomming(void)
{
	CDC_Transmit_FS( answer, sizeof( answer));
}
