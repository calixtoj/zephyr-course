cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(led_sensor_driver_lab)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(app PRIVATE
    src/main.cpp
    drivers/sensor/led_sensor/led_sensor.c
)