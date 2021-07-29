#include "iot_os_util.h"

#define GPIO_OUTPUT_MAINLED 2
#define GPIO_OUTPUT_MAINLED_0 13 /* use as ground */

#define TEMPERATURE_EVENT_MS_RATE 10000
#define BUZZER_SOUND_DURATION 3000
#define RGB_BOILING_ADJUSTMENT_DURATION 20

// init rgb values -- green 
#define RGB_LED_R 0
#define RGB_LED_G 255
#define RGB_LED_B 0


enum switch_onoff_state {
    SWITCH_OFF = 0,
    SWITCH_ON = 1,
};

enum thermostat_onoff_state {
    THERMOSTAT_OFF = 0,
    THERMOSTAT_ON = 1,
};

enum buzzer_onoff_state {
    BUZZER_OFF = 0,
    BUZZER_ON = 1,
};

enum main_led_gpio_state {
    MAINLED_GPIO_ON = 1,
    MAINLED_GPIO_OFF = 0,
};

void change_switch_state(int switch_state);
void change_thermostat_state(int *thermostat_state);
// void led_blink(int switch_state, int delay, int count);
void iot_gpio_init(void);
void change_led_state(double heating_setpoint, int led_state);
int get_temperature_event(iot_os_timer timer);
double temperature_event(double temperature_value);
void change_rgb_led_boiling(double heating_setpoint, double current_temperature);
void change_rgb_led_state(int red, int green, int blue);
void beep();