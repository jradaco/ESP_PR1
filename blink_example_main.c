/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
     ____
    |    |
     ----
    |    |
     ____
*/
/* Define GPIO to OUTPUTS */
#define DISP_SEG_A 16u
#define DISP_SEG_B 17u
#define DISP_SEG_C 18u
#define DISP_SEG_D 19u
#define DISP_SEG_E 21u
#define DISP_SEG_F 22u
#define DISP_SEG_G 23u
/*Define GPIO to INPUTS */
#define SW1 25
#define SW2 26
#define SW3 27

#define SEGMENTS_PORT GPIO
#define TIMEPULSE 500

typedef int esp_err_t;

static uint8_t s_led_state = 0;

static void blink_led(void)
{
	/* Set the GIPIO DISP_SEG_x  (HIGH-> LOW) TO FORM
	*       |
	*       |
	*/
	s_led_state = 1;
    gpio_set_level(DISP_SEG_E, s_led_state);
    gpio_set_level(DISP_SEG_F, s_led_state);

    vTaskDelay(TIMEPULSE / portTICK_PERIOD_MS);
    /* Toggle the LED state */
    s_led_state = !s_led_state;
    gpio_set_level(DISP_SEG_E, s_led_state);
    gpio_set_level(DISP_SEG_F, s_led_state);
    vTaskDelay(TIMEPULSE / portTICK_PERIOD_MS);

}

static void blink_led1(void)
{

	/* Set the GIPIO DISP_SEG_x  (HIGH-> LOW) TO FORM
	*          __
	*          __
	*          __
	*/
	s_led_state = 1;
	gpio_set_level(DISP_SEG_A, s_led_state);
    gpio_set_level(DISP_SEG_D, s_led_state);

    gpio_set_level(DISP_SEG_G, s_led_state);
    vTaskDelay(TIMEPULSE / portTICK_PERIOD_MS);
    /* Toggle the LED state */
    s_led_state = !s_led_state;
    gpio_set_level(DISP_SEG_A, s_led_state);
    gpio_set_level(DISP_SEG_D, s_led_state);
    gpio_set_level(DISP_SEG_G, s_led_state);
    vTaskDelay(TIMEPULSE / portTICK_PERIOD_MS);
}

static void blink_led2(void)
{

	/* Set the GIPIO DISP_SEG_x  (HIGH-> LOW) TO FORM
	*            |
	*            |
	*/
	s_led_state = 1;
    gpio_set_level(DISP_SEG_B, s_led_state);
    gpio_set_level(DISP_SEG_C, s_led_state);
    vTaskDelay(TIMEPULSE / portTICK_PERIOD_MS);
    /* Toggle the LED state */
    s_led_state = !s_led_state;
    gpio_set_level(DISP_SEG_B, s_led_state);
    gpio_set_level(DISP_SEG_C, s_led_state);
    vTaskDelay(TIMEPULSE / portTICK_PERIOD_MS);
    s_led_state = !s_led_state;
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(DISP_SEG_A);
    gpio_reset_pin(DISP_SEG_B);
    gpio_reset_pin(DISP_SEG_C);
    gpio_reset_pin(DISP_SEG_D);
    gpio_reset_pin(DISP_SEG_E);
    gpio_reset_pin(DISP_SEG_F);
    gpio_reset_pin(DISP_SEG_G);

    /* reset inputs */
    gpio_reset_pin(SW1);
    gpio_reset_pin(SW2);
    gpio_reset_pin(SW3);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(DISP_SEG_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(DISP_SEG_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(DISP_SEG_C, GPIO_MODE_OUTPUT);
    gpio_set_direction(DISP_SEG_D, GPIO_MODE_OUTPUT);
    gpio_set_direction(DISP_SEG_E, GPIO_MODE_OUTPUT);
    gpio_set_direction(DISP_SEG_F, GPIO_MODE_OUTPUT);
    gpio_set_direction(DISP_SEG_G, GPIO_MODE_OUTPUT);

    /* Set the GPIO as input */
    gpio_set_direction(SW1, GPIO_MODE_INPUT);
    gpio_set_direction(SW2, GPIO_MODE_INPUT);
    gpio_set_direction(SW3, GPIO_MODE_INPUT);
}

void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();

    while (1) {

    	int inputState1 = gpio_get_level(SW1);
    	int inputState2 = gpio_get_level(SW2);
    	int inputState3 = gpio_get_level(SW3);


    	if (inputState1 == 1){
    		blink_led();
    	}

    	if (inputState1 == 1 && inputState2 == 1){
    	    blink_led();
    	    blink_led1();
    	}

    	if (inputState1 == 1 && inputState2 == 1 && inputState3 == 1){
    		blink_led();
    	    blink_led1();
    	    blink_led2();
    	}

    }
}
