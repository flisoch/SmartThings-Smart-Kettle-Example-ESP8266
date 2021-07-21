#include "device_control.h"
#include "driver/gpio.h"

#include "iot_os_util.h"

void change_switch_state(int switch_state)
{
    if (switch_state == SWITCH_OFF) {
        gpio_set_level(GPIO_OUTPUT_MAINLED, MAINLED_GPIO_OFF);
    } else {
        gpio_set_level(GPIO_OUTPUT_MAINLED, MAINLED_GPIO_ON);
    }
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
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_MAINLED_0;
	gpio_config(&io_conf);


	gpio_install_isr_service(0);

	gpio_set_level(GPIO_OUTPUT_MAINLED, MAINLED_GPIO_ON);
	gpio_set_level(GPIO_OUTPUT_MAINLED_0, 0);
}

void change_led_state(double heating_setpoint, int led_state)
{
	// any signalling of chosen temperature/heating mode
	if (heating_setpoint > 30) {
		change_switch_state(!led_state);
		iot_os_delay(300);
		change_switch_state(led_state);
		iot_os_delay(300);
		change_switch_state(!led_state);
		iot_os_delay(300);
		change_switch_state(led_state);
	}
	else  {
		change_switch_state(!led_state);
		iot_os_delay(800);
		change_switch_state(led_state);
		iot_os_delay(800);
		change_switch_state(!led_state);
		iot_os_delay(800);
		change_switch_state(led_state);
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
        printf("SILENCE!\n");
    } else {
        printf("BEEP!\n");
    }
}
void beep() {
	/* emulate buzzer */
	change_buzzer_state(BUZZER_ON);
	IOT_DELAY(BUZZER_SOUND_DURATION);
	change_buzzer_state(BUZZER_OFF);
}