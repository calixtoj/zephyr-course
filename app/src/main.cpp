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

	while (1) {
		int ret = sensor_sample_fetch(led_sensor);
		if (ret < 0) {
			LOG_ERR("sensor_sample_fetch failed: %d", ret);
			return 0;
		}

		ret = sensor_channel_get(led_sensor, SENSOR_CHAN_LED_STATE, &val);
		if (ret < 0) {
			LOG_ERR("sensor_channel_get failed: %d", ret);
			return 0;
		}

		LOG_INF("LED state: %d", val.val1);

		k_sleep(K_MSEC(CONFIG_LED_BLINK_SLEEP_TIME_MS));
	}

	return 0;
}