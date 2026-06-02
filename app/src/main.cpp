#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <stdlib.h>

#include "led_sensor.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define LED_SENSOR_NODE DT_NODELABEL(led_sensor0)

static const struct device *get_led_sensor_dev(void)
{
	static const struct device *dev = DEVICE_DT_GET(LED_SENSOR_NODE);
	return dev;
}

static int cmd_sensor_set(const struct shell *shell,
			  size_t argc,
			  char **argv)
{
	const struct device *dev = get_led_sensor_dev();

	if (!device_is_ready(dev)) {
		shell_error(shell, "LED sensor device is not ready");
		return -ENODEV;
	}

	int value = atoi(argv[1]);

	if ((value != 0) && (value != 1)) {
		shell_error(shell, "Invalid value: %s. Use 0 or 1", argv[1]);
		return -EINVAL;
	}

	int ret = led_sensor_set_blink_enabled(dev, value == 1);
	if (ret < 0) {
		shell_error(shell, "led_sensor_set_blink_enabled failed: %d", ret);
		return ret;
	}

	shell_print(shell, "Blink enabled: %s", value ? "true" : "false");

	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_cmds,
	SHELL_CMD_ARG(set,
		      NULL,
		      "Enable/disable LED blinking: sensor set <0|1>",
		      cmd_sensor_set,
		      2,
		      0),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor,
		   &sensor_cmds,
		   "LED sensor commands",
		   NULL);


int main(void)
{
	const struct device *led_sensor = get_led_sensor_dev();
	struct sensor_value val;

	if (!device_is_ready(led_sensor)) {
		LOG_ERR("LED sensor device is not ready");
		return 0;
	}

	LOG_INF("LED sensor device ready");

	int counter = 0;

	while (1) {
		sensor_sample_fetch(led_sensor);
		sensor_channel_get(led_sensor, SENSOR_CHAN_LED_STATE, &val);

		//LOG_INF("LED state: %d", val.val1);


		k_sleep(K_MSEC(CONFIG_LED_BLINK_SLEEP_TIME_MS));
}

	return 0;
}