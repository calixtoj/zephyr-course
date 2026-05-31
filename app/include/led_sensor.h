#ifndef LED_SENSOR_H_
#define LED_SENSOR_H_

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdbool.h>

#define SENSOR_CHAN_LED_STATE SENSOR_CHAN_PRIV_START

typedef int (*led_sensor_set_blink_enabled_t)(const struct device *dev,
					      bool enabled);

struct led_sensor_driver_api {
	struct sensor_driver_api sensor_api;
	led_sensor_set_blink_enabled_t set_blink_enabled;
};

static inline int led_sensor_set_blink_enabled(const struct device *dev,
					       bool enabled)
{
	const struct led_sensor_driver_api *api =
		(const struct led_sensor_driver_api *)dev->api;

	return api->set_blink_enabled(dev, enabled);
}

#endif /* LED_SENSOR_H_ */