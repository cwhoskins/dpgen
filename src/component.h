/*
 * component.h
 *
 *  Created on: Oct 17, 2020
 *      Author: cwhos
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "net.h"

typedef enum enum_comp_type {
	load_register,
	adder,
	subtractor,
	multiplier,
	comparator,
	mux2x1,
	shift_right,
	shift_left,
	divider,
	modulo,
	incrementer,
	decrementer
} component_type;

//typedef struct struct_component {
//	component_type type;
//	float delay;
//	net* inputs;
//	net* outputs;
//} component;
//
//component* InitializeComponent(char* name, net_type type);
//uint8_t SetInput(component* cur_component, net* input, uint8_t input_idx);
//uint8_t SetOutput(component* cur_component, net* output, uint8_t output_idx);


#endif /* COMPONENT_H_ */
