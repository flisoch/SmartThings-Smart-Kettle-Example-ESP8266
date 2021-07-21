#include "iot_os_util.h"

#define GPIO_OUTPUT_MAINLED 2
#define GPIO_OUTPUT_MAINLED_0 13 /* use as ground */

#define TEMPERATURE_EVENT_MS_RATE 10000

enum switch_onoff_state {
    SWITCH_OFF = 0,
    SWITCH_ON = 1,
};

enum main_led_gpio_state {
    MAINLED_GPIO_ON = 1,
    MAINLED_GPIO_OFF = 0,
};

void change_switch_state(int switch_state);
// void led_blink(int switch_state, int delay, int count);
void iot_gpio_init(void);
void change_led_state(double heating_setpoint, int led_state);
int get_temperature_event(iot_os_timer timer);
double temperature_event(double temperature_value);