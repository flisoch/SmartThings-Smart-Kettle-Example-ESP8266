#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "st_dev.h"
#include "caps_temperatureAlarm.h"

static const char *caps_temperatureAlarm_get_value(caps_temperatureAlarm_data_t *caps_data)
{
    if (!caps_data) {
        printf("caps_data is NULL\n");
        return NULL;
    }
    return caps_data->value;
}

static void caps_temperatureAlarm_set_value(caps_temperatureAlarm_data_t *caps_data, const char *value)
{
    if (!caps_data) {
        printf("caps_data is NULL\n");
        return;
    }
    caps_data->value = (char *)value;
}

static void caps_temperatureAlarm_attr_value_send(caps_temperatureAlarm_data_t *caps_data)
{
    int sequence_no = -1;

    if (!caps_data || !caps_data->handle) {
        printf("fail to get handle\n");
        return;
    }

    ST_CAP_SEND_ATTR_STRING(caps_data->handle,
            (char *)caps_helper_temperatureAlarm.attr_temperatureAlarm.name,
            caps_data->value,
            NULL,
            NULL,
            sequence_no);

    if (sequence_no < 0)
        printf("fail to send temperature value\n");
    else
        printf("Sequence number return : %d\n", sequence_no);
}

static void caps_init_cb(IOT_CAP_HANDLE *handle, void *usr_data)
{
    caps_temperatureAlarm_data_t *caps_data = usr_data;
    if (caps_data && caps_data->init_usr_cb)
        caps_data->init_usr_cb(caps_data);
    caps_temperatureAlarm_attr_value_send(caps_data);
}

caps_temperatureAlarm_data_t *caps_temperatureAlarm_initialize(IOT_CTX *ctx, const char *component, void *init_usr_cb, void *usr_data) {
    caps_temperatureAlarm_data_t *caps_data = NULL;
    caps_data = malloc(sizeof(caps_temperatureAlarm_data_t));
    if (!caps_data) {
        printf("fail to malloc for caps_temperatureAlarm_data_t\n");
        return NULL;
    }

    memset(caps_data, 0, sizeof(caps_temperatureAlarm_data_t));

    caps_data->init_usr_cb = init_usr_cb;
    caps_data->usr_data = usr_data;

    caps_data->get_value = caps_temperatureAlarm_get_value;
    caps_data->set_value = caps_temperatureAlarm_set_value;
    caps_data->attr_temperatureAlarm_send = caps_temperatureAlarm_attr_value_send;
    caps_data->value = (char *)caps_helper_temperatureAlarm.attr_temperatureAlarm.value_heat;
    if (ctx) {
        caps_data->handle = st_cap_handle_init(ctx, component, caps_helper_temperatureAlarm.id, caps_init_cb, caps_data);
    }
    if (!caps_data->handle) {
        printf("fail to init temperatureSensor handle\n");
    }

    return caps_data;
}
