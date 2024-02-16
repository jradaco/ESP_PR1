/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
 //#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
#include "driver/gpio.h"

#include "esp_log.h"

#include "sdkconfig.h"

#include "esp_timer.h"

static
const char * TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
     ____
    |    |
     ----
    |    |
     ____
*/
/* Define GPIO to OUTPUTS */
#define DISP_SEG_A 12
#define DISP_SEG_B 14
#define DISP_SEG_C 21
#define DISP_SEG_D 22
#define DISP_SEG_E 23
#define DISP_SEG_F 13
#define DISP_SEG_G 27
/*Define GPIO to INPUTS */
#define SW1 4
#define SW2 5
#define SW3 18

#define SEGMENTS_PORT GPIO
#define TIMEPULSE 500

typedef int esp_err_t;

static void configure_led(void) {
  ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
  gpio_reset_pin(DISP_SEG_A);
  gpio_reset_pin(DISP_SEG_B);
  gpio_reset_pin(DISP_SEG_C);
  gpio_reset_pin(DISP_SEG_D);
  gpio_reset_pin(DISP_SEG_E);
  gpio_reset_pin(DISP_SEG_F);
  gpio_reset_pin(DISP_SEG_G);

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

  gpio_set_direction(SW1, GPIO_MODE_INPUT);
  gpio_set_direction(SW2, GPIO_MODE_INPUT);
  gpio_set_direction(SW3, GPIO_MODE_INPUT);

}

static void blink_f_e(int state) {
  gpio_set_level(DISP_SEG_F, state);
  gpio_set_level(DISP_SEG_E, state);

}

static void blink_a_g_d(int state) {
  gpio_set_level(DISP_SEG_A, state);
  gpio_set_level(DISP_SEG_G, state);
  gpio_set_level(DISP_SEG_D, state);

}

static void blink_b_c(int state) {
  gpio_set_level(DISP_SEG_B, state);
  gpio_set_level(DISP_SEG_C, state);

}

void delay_using_timer(int delay_in_us) {
  int start_time = esp_timer_get_time();
  int end_time = start_time + delay_in_us; // delay_in_us is the delay in microseconds
  while (esp_timer_get_time() < end_time) {
    // Do nothing, just wait
  }
}

void app_main(void) {

  /* Configure the peripheral according to the LED type */
  configure_led();

  int last_time_f_e = 0;
  int last_time_a_g_d = 0;
  int last_time_b_c = 0;
  const int delay_us = 500 * 1000; // 0.5 segundo en microsegundos

  int last_value_f_e = 1;
  int last_value_a_g_d = 1;
  int last_value_b_c = 1;

  while (1) {

    int current_time = esp_timer_get_time();

    int inputState1 = gpio_get_level(SW1);
    int inputState2 = gpio_get_level(SW2);
    int inputState3 = gpio_get_level(SW3);

    if (current_time - last_time_f_e >= delay_us && inputState1 == 1 && last_value_a_g_d == 1 && last_value_b_c == 1) {

      blink_f_e(!last_value_f_e);
      last_time_f_e = current_time; // Actualiza el tiempo de inicio
      last_value_f_e = !last_value_f_e;

    }

    if (current_time - last_time_a_g_d >= delay_us && inputState2 == 1 && last_value_f_e == 1 && last_value_b_c == 1) {
      blink_a_g_d(!last_value_a_g_d);
      last_time_a_g_d = current_time; // Actualiza el tiempo de inicio
      last_value_a_g_d = !last_value_a_g_d;

    }

    if (current_time - last_time_b_c >= delay_us && inputState3 == 1 && last_value_f_e == 1 && last_value_a_g_d == 1) {
      blink_b_c(!last_value_b_c);
      last_time_b_c = current_time; // Actualiza el tiempo de inicio
      last_value_b_c = !last_value_b_c;

    }

  }
}
