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

#define FALSE 0
#define TRUE 1

//
#define DP_OUT_IDX 0

#define CTRL_IN_IDX 0

#define DP_IN_A_IDX 0
#define DP_IN_B_IDX 1

#define LT_IDX 0
#define EQ_IDX 1
#define GT_IDX 2

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

typedef struct struct_component component;

//Circuit
typedef struct struct_circuit circuit;

#endif /* GLOBAL_H_ */
