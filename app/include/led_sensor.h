#ifndef LED_SENSOR_H_
#define LED_SENSOR_H_

#include <zephyr/drivers/sensor.h>

/*
 * Canal privado para leer el estado del LED.
 * val1 = 0 apagado
 * val1 = 1 encendido
 */
#define SENSOR_CHAN_LED_STATE SENSOR_CHAN_PRIV_START

#endif /* LED_SENSOR_H_ */