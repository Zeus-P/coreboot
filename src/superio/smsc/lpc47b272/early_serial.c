/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2005 Digital Design Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* Pre-RAM driver for SMSC LPC47B272 Super I/O chip. */

#include <arch/io.h>
#include <device/pnp_ops.h>
#include <device/pnp.h>
#include <stdint.h>
#include "lpc47b272.h"

static void pnp_enter_conf_state(pnp_devfn_t dev)
{
	u16 port = dev >> 8;
	outb(0x55, port);
}

static void pnp_exit_conf_state(pnp_devfn_t dev)
{
	u16 port = dev >> 8;
	outb(0xaa, port);
}

/**
 * Configure the base I/O port of the specified serial device and enable the
 * serial device.
 *
 * @param dev High 8 bits = Super I/O port, low 8 bits = logical device number.
 * @param iobase Processor I/O port address to assign to this serial device.
 */
void lpc47b272_enable_serial(pnp_devfn_t dev, u16 iobase)
{
	pnp_enter_conf_state(dev);
	pnp_set_logical_device(dev);
	pnp_set_enable(dev, 0);
	pnp_set_iobase(dev, PNP_IDX_IO0, iobase);
	pnp_set_enable(dev, 1);
	pnp_exit_conf_state(dev);
}
