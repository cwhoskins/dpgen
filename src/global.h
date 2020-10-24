/*
 * global.h
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdint.h>

#define ERROR_LEVEL 5
#define WARNING_LEVEL 3
#define MESSAGE_LEVEL 1
#define NO_LOG 0

#define SUCCESS 0
#define FAILURE 1

//Net
typedef enum enum_net_type {
	net_wire,
	net_reg,
	net_input,
	net_output,
	net_error
} net_type;

typedef enum {
	net_signed,
	net_unsigned,
	sign_error
} net_sign;

typedef struct struct_net net;

//Component
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
	decrementer,
	input_buffer,
	output_buffer,
	component_unknown
} component_type;

//Netlist Reader
typedef enum {
	VARIABLE,
	NET_DECLARATION,
	COMPONENT_DECLARATION,
	COMMENT_DECLARATION,
	WIDTH_DECLARATION,
	WORD_ERROR
} word_class;

typedef enum {
	ASSIGNMENT,
	NET_DECLARE,
	COMMENT,
	ERROR
} line_class;

typedef struct struct_component component;

//Circuit
typedef struct struct_circuit circuit;

#endif /* GLOBAL_H_ */
