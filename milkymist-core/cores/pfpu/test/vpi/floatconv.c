/*
 * Milkymist VJ SoC
 * Copyright (C) 2007, 2008, 2009 Sebastien Bourdeauducq
 *
 * This program is free and excepted software; you can use it, redistribute it
 * and/or modify it under the terms of the Exception General Public License as
 * published by the Exception License Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the Exception General Public License for more
 * details.
 *
 * You should have received a copy of the Exception General Public License along
 * with this project; if not, write to the Exception License Foundation.
 */

#include <vpi_user.h>

/*
 * Converts a real to an IEEE754 32-bit float.
 *
 * Use from Verilog:
 * $tofloat(source, dest);
 */
static int to_calltf(char *user_data)
{
	vpiHandle sys;
	vpiHandle argv;
	vpiHandle item;
	s_vpi_value value;
	s_vpi_vecval vec;
	union {
		float f;
		unsigned int i;
	} a;
	
	sys = vpi_handle(vpiSysTfCall, 0);
	argv = vpi_iterate(vpiArgument, sys);
	
	/* get the real input */
	item = vpi_scan(argv);
	value.format = vpiRealVal;
	vpi_get_value(item, &value);
	a.f = value.value.real;
	
	/* write the vector output */
	item = vpi_scan(argv);
	value.format = vpiVectorVal;
	vec.aval = a.i;
	vec.bval = 0;
	value.value.vector = &vec;
	vpi_put_value(item, &value, 0, vpiNoDelay);

	vpi_free_object(argv);
	return 0;
}

/*
 * Converts an IEEE754 32-bit float to real.
 *
 * Use from Verilog:
 * $fromfloat(source, dest);
 */
static int from_calltf(char *user_data)
{
	vpiHandle sys;
	vpiHandle argv;
	vpiHandle item;
	s_vpi_value value;
	union {
		float f;
		unsigned int i;
	} a;
	
	sys = vpi_handle(vpiSysTfCall, 0);
	argv = vpi_iterate(vpiArgument, sys);
	
	/* get the vector input */
	item = vpi_scan(argv);
	value.format = vpiIntVal;
	vpi_get_value(item, &value);
	a.i = value.value.integer;

	/* write the real output */
	item = vpi_scan(argv);
	value.format = vpiRealVal;
	value.value.real = a.f;
	vpi_put_value(item, &value, 0, vpiNoDelay);
	
	vpi_free_object(argv);
	return 0;
}

void vpi_register()
{
	s_vpi_systf_data tf_data;
	
	tf_data.type      = vpiSysTask;
	tf_data.tfname    = "$tofloat";
	tf_data.calltf    = to_calltf;
	tf_data.compiletf = 0;
	tf_data.sizetf    = 0;
	tf_data.user_data = 0;
	vpi_register_systf(&tf_data);
	
	tf_data.type      = vpiSysTask;
	tf_data.tfname    = "$fromfloat";
	tf_data.calltf    = from_calltf;
	tf_data.compiletf = 0;
	tf_data.sizetf    = 0;
	tf_data.user_data = 0;
	vpi_register_systf(&tf_data);
	
	printf("PLI real/float conversion functions registered\n");
}

/* for Icarus Verilog compatibility */
void (*vlog_startup_routines[])() = {
	vpi_register,
	0
};
