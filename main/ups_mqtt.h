#ifndef UPS_MQTT_H
#define UPS_MQTT_H

#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_tls.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "ups.h"
#include "esp_system.h"

#define MAX_IDENTIFIERS 1
#define MAX_STRING_LENGTH 64
#define MAX_AVAILABILITY 1

#define URI_BROKER CONFIG_BROKER_URL

// Define topic to setup mqtt discovery

#define TOPIC_SETUP "homeassistant/sensor/"
#define TOPIC_CONFIG "config"

// Define a struct for type and unit
typedef struct
{
    char *type;
    char *unit;
    char *device;
    char *name;

} TypeInfo;

// Category os UPS

#define TYPE_POWER_OUT_PERCENT "power_out_percent"
#define TYPE_CURRENT_OUT "current_out"
#define TYPE_VOLTAGE_OUT "voltage_out"
#define TYPE_VOLTAGE_IN "voltage_in"
#define TYPE_POWER_OUT "power_out"
#define TYPE_POWER_IN "power_in"
#define TYPE_TEMPERATURE "temperature"
#define TYPE_BATTERY_STATE "battery_state"
#define TYPE_BATTERY_VOLTAGE "battery_voltage"
#define TYPE_FREQUENCY "frequency"

#define DEVICE_POWER_OUT_PERCENT "power"
#define DEVICE_CURRENT_OUT "current"
#define DEVICE_VOLTAGE_OUT "voltage"
#define DEVICE_VOLTAGE_IN "voltage"
#define DEVICE_POWER_OUT "power"
#define DEVICE_POWER_IN "power"
#define DEVICE_TEMPERATURE "temperature"
#define DEVICE_BATTERY_STATE "battery"
#define DEVICE_BATTERY_VOLTAGE "voltage"
#define DEVICE_FREQUENCY "frequency"

#define NAME_POWER_OUT_PERCENT "Power Out %"
#define NAME_CURRENT_OUT "Current Out"
#define NAME_VOLTAGE_OUT "Voltage Out"
#define NAME_VOLTAGE_IN "Voltage In"
#define NAME_POWER_OUT "Power Out"
#define NAME_POWER_IN "Power IN"
#define NAME_TEMPERATURE "Temperatura"
#define NAME_BATTERY_STATE "Battery State"
#define NAME_BATTERY_VOLTAGE "Battery Voltage"
#define NAME_FREQUENCY "Frequency"


// Fixed values from the JSON MQTT Setup
#define TOPIC_0 "UPS_ESP32_tinySrv/%s/availability"
#define VALUE_TEMPLATE_0 "{{ value_json.state }}"
#define AVAILABILITY_MODE "all"
#define IDENTIFIER_0 "UPS_ESP32_tinySrv_%s"
#define MANUFACTURER "Lucas Souza"
#define MODEL "UPS_ESP32_tinySrv"
#define NAME "UPS_ESP32_tinySrv_Sensor_%s"
#define VIA_DEVICE "UPS_ESP32_tinySrv_bridge_%s"
#define DEVICE_CLASS "%s"
#define OBJECT_ID "sensor_ups_%s"
#define ORIGIN_NAME "UPS_ESP32_tinySrv"
#define ORIGIN_SW "1.0.0"
#define ORIGIN_URL "https://github.com/antunesls/UPS_ESP32_tinySrv"
#define STATE_CLASS "measurement"
#define STATE_TOPIC "UPS_ESP32_tinySrv/%s/Sensor_%s"
#define UNIQUE_ID "%s_%s_UPS_ESP32_tinySrv"
#define UNIT_OF_MEASUREMENT "%s"
#define VALUE_TEMPLATE "{{ value_json.%s }}"

typedef struct
{
    char topic[MAX_STRING_LENGTH];
    char value_template[MAX_STRING_LENGTH];
} Availability;

typedef struct
{
    char identifiers[MAX_IDENTIFIERS][MAX_STRING_LENGTH];
    char manufacturer[MAX_STRING_LENGTH];
    char model[MAX_STRING_LENGTH];
    char name[MAX_STRING_LENGTH];
    char via_device[MAX_STRING_LENGTH];
} Device;

typedef struct
{
    char name[MAX_STRING_LENGTH];
    char sw[MAX_STRING_LENGTH];
    char url[MAX_STRING_LENGTH];
} Origin;

typedef struct
{
    Availability availability[MAX_AVAILABILITY];
    int availability_count; // Number of availability entries
    char availability_mode[MAX_STRING_LENGTH];
    Device device;
    char device_class[MAX_STRING_LENGTH];
    bool enabled_by_default;
    char object_id[MAX_STRING_LENGTH];
    Origin origin;
    char name[MAX_STRING_LENGTH];
    char state_class[MAX_STRING_LENGTH];
    char state_topic[MAX_STRING_LENGTH];
    char unique_id[MAX_STRING_LENGTH];
    char unit_of_measurement[MAX_STRING_LENGTH];
    char value_template[MAX_STRING_LENGTH];
} SensorData;

extern esp_mqtt_client_handle_t client;

// Declarações de funções
void mqtt_app_start(void);
void publish_metrics(const ups_metricts_t *metrics);

#endif // MQTT_MANAGER_H
