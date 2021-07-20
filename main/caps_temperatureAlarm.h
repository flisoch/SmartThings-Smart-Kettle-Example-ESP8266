#include "caps/iot_caps_helper_temperatureAlarm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct caps_temperatureAlarm_data {
    IOT_CAP_HANDLE *handle;
    void *usr_data;
    void *cmd_data;

    char *value;

    const char *(*get_value)(struct caps_temperatureAlarm_data *caps_data);
    void (*set_value)(struct caps_temperatureAlarm_data *caps_data, const char *value);
    void (*attr_temperatureAlarm_send)(struct caps_temperatureAlarm_data *caps_data);

    void (*init_usr_cb)(struct caps_temperatureAlarm_data *caps_data);
} caps_temperatureAlarm_data_t;

caps_temperatureAlarm_data_t *caps_temperatureAlarm_initialize(IOT_CTX *ctx, const char *component, void *init_usr_cb, void *usr_data);
#ifdef __cplusplus
}
#endif
