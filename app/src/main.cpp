#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include "led_sensor.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define LED_SENSOR_NODE DT_NODELABEL(led_sensor0)

int main(void)
{
	const struct device *led_sensor = DEVICE_DT_GET(LED_SENSOR_NODE);
	struct sensor_value val;

	if (!device_is_ready(led_sensor)) {
		LOG_ERR("LED sensor device is not ready");
		return 0;
	}

	LOG_INF("LED sensor device ready");

	int counter = 0;

	while (1) {
		if (counter == 5) {
			LOG_INF("Disabling LED blinking");
			led_sensor_set_blink_enabled(led_sensor, false);
		}

		if (counter == 10) {
			LOG_INF("Enabling LED blinking again");
			led_sensor_set_blink_enabled(led_sensor, true);
			counter = 0;
		}

		sensor_sample_fetch(led_sensor);
		sensor_channel_get(led_sensor, SENSOR_CHAN_LED_STATE, &val);

		LOG_INF("LED state: %d", val.val1);

		counter++;

		k_sleep(K_MSEC(CONFIG_LED_BLINK_SLEEP_TIME_MS));
}

	return 0;
}