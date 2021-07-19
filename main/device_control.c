#include "device_control.h"

#include "driver/gpio.h"

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