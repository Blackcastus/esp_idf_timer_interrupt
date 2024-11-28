#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

uint16_t count = 0;

void IRAM_ATTR timer_callback(void *param)
{
	count++;
}

void Timer_Init(void)
{
	const esp_timer_create_args_t my_timer_args =
	{
		.callback 	= &timer_callback,
		.arg		= NULL,
		.name 		= "Timer Interrupt"
	};

	esp_timer_handle_t timer_handler;
	esp_timer_create(&my_timer_args, &timer_handler);
	esp_timer_start_periodic(timer_handler, 1000000); // One second = 1000000 micro second
	// Log initialization
    ESP_LOGI("TIMER", "Timer initialized and started.");
}

void app_main(void)
{
	Timer_Init();

	while(1)
	{
		ESP_LOGI("TIMER", "time: %d\n", count);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}