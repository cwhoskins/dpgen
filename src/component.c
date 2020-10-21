/*
 * component.c
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */
#include "component.h"
#include "net.h"


typedef struct struct_component {
	component_type type;
	float delay;
	net_sign sign;
	net* inputs;
	net* outputs;
} component;


