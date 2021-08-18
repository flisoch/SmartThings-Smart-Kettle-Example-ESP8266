#include "device_control.h"
#include "driver/gpio.h"
#include "driver/pwm.h"

#include "iot_os_util.h"
#include <math.h>

void change_switch_state(int switch_state)
{
    if (switch_state == SWITCH_OFF) {
        gpio_set_level(GPIO_OUTPUT_MAINLED, LED_GPIO_OFF);
    } else {
        gpio_set_level(GPIO_OUTPUT_MAINLED, LED_GPIO_ON);
    }
}

void change_thermostat_state(int *thermostat_state)
{
    if (thermostat_state == THERMOSTAT_OFF) {
		*thermostat_state = THERMOSTAT_ON;
    } else {
		*thermostat_state = THERMOSTAT_OFF;
    }
}
int get_button_event()
{
    static uint32_t button_last_state = 0;
    uint32_t gpio_level = 0;

    gpio_level = gpio_get_level(GPIO_INPUT_SWITCH);
    if (button_last_state != gpio_level) {
        /* wait debounce time to ignore small ripple of currunt */
        IOT_DELAY(BUTTON_DEBOUNCE_TIME_MS);
        gpio_level = gpio_get_level(GPIO_INPUT_SWITCH);
        if (button_last_state != gpio_level) {
            printf("Button event, val: %d, \n", gpio_level);
            button_last_state = gpio_level;           
        }
		return 1;
    }

    return 0;
}

void iot_gpio_init(void)
{   
    // esp sdk specific 
	gpio_config_t io_conf;

	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_MAINLED;
	io_conf.pull_down_en = 1;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_BUZZER;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_RGBLED_R;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_RGBLED_G;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_RGBLED_B;
	gpio_config(&io_conf);
	io_conf.intr_type = GPIO_INTR_ANYEDGE;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pin_bit_mask = 1 << GPIO_INPUT_SWITCH;
	io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
	gpio_config(&io_conf);

	gpio_install_isr_service(0);

	gpio_set_level(GPIO_OUTPUT_MAINLED, LED_GPIO_ON);
	gpio_set_level(GPIO_OUTPUT_BUZZER, LED_GPIO_OFF);
	gpio_set_level(GPIO_OUTPUT_RGBLED_R, LED_GPIO_OFF);
	gpio_set_level(GPIO_OUTPUT_RGBLED_G, LED_GPIO_OFF);
	gpio_set_level(GPIO_OUTPUT_RGBLED_B, LED_GPIO_ON);
}

void change_rgb_state(int pin, int value)
{
	if (pin == GPIO_OUTPUT_RGBLED_R) {
		gpio_set_level(GPIO_OUTPUT_RGBLED_R, value);
	}
	else if (pin == GPIO_OUTPUT_RGBLED_G) {
		gpio_set_level(GPIO_OUTPUT_RGBLED_G, value);
	}
	else if (pin == GPIO_OUTPUT_RGBLED_B) {
		gpio_set_level(GPIO_OUTPUT_RGBLED_B, value);
	}
}

void change_led_state(double heating_setpoint, int led_state)
{
	// any signalling of chosen temperature/heating mode
	int blinks = 0;
	if (heating_setpoint <= 10) {
		blinks = 1;
	}
	else if (heating_setpoint <= 20)
	{
		blinks = 2;
	}
	else if (heating_setpoint <= 50) {
		blinks = 3;
	}
	else if (heating_setpoint <= 100) {
		blinks = 4;
	}
	else {
		printf("heating setpoint is more than 100 or not set!\nPlease, set correct number");
	}
	for (int i = 0; i < blinks; i++) {
		// todo: мигать rgb зелёным светодиодом
		change_switch_state(1 - led_state);
		iot_os_delay(300);
		change_switch_state(led_state);
		iot_os_delay(300);
	}
}

int get_temperature_event(iot_os_timer timer)
{
    if (iot_os_timer_isexpired(timer)) {
	    iot_os_timer_count_ms(timer, TEMPERATURE_EVENT_MS_RATE);
		return 1;
	}
	else {
		return 0;
	}
}

double temperature_event(double temperature_value) {
    /* emulate sensor value for example */
    return temperature_value + 5;
}

void change_buzzer_state(int buzzer_state) 
{	
	if (buzzer_state == BUZZER_OFF) {
		gpio_set_level(GPIO_OUTPUT_BUZZER, BUZZER_OFF);
        printf("SILENCE!\n");
    } else {
		gpio_set_level(GPIO_OUTPUT_BUZZER, BUZZER_ON);
        printf("BEEP!\n");
    }
}
void beep() {
	change_buzzer_state(BUZZER_ON);
	IOT_DELAY(BUZZER_SOUND_DURATION);
	change_buzzer_state(BUZZER_OFF);
}

