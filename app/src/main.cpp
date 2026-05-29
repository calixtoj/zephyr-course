/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <stdio.h>

static int board_init(void)
{
	printf("Board Initialized\n");
	return 0;
}

/* Ejecuta antes de main() */
SYS_INIT(board_init, APPLICATION, 0);

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	return 0;
}