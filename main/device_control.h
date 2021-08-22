#include "iot_os_util.h"

#define GPIO_OUTPUT_MAINLED 2
#define GPIO_INPUT_SWITCH 5
#define GPIO_OUTPUT_BUZZER 4
#define GPIO_OUTPUT_RGBLED_R 13 
#define GPIO_OUTPUT_RGBLED_G 12
#define GPIO_OUTPUT_RGBLED_B 14

#define TEMPERATURE_EVENT_MS_RATE 10000
#define BUZZER_SOUND_DURATION 3000
#define RGB_BOILING_ADJUSTMENT_DURATION 20
#define BUTTON_DEBOUNCE_TIME_MS 20
#define BLINK_DURATION 300

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

enum led_gpio_state {
    LED_GPIO_ON = 1,
    LED_GPIO_OFF = 0,
};

void change_switch_state(int switch_state);
void change_thermostat_state(int *thermostat_state);
void iot_gpio_init(void);
void blink_led(double heating_setpoint, int led_state);
int get_temperature_event(iot_os_timer timer);
double temperature_event(double temperature_value);
void change_rgb_state(int pin, int value);
void beep();
int get_button_event();