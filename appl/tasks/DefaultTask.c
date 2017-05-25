/*
 * DefaultTask.c
 *
 *  Created on: 22.04.2017
 *      Author: manni1user
 */



#include "intersect/DefaultTask.h"

#include "stm32f1xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

void DefaultTaskEntry(void)
{
	//printf("Hallo");
	while(1)
	{
		vTaskDelay(1000);
	}
}

