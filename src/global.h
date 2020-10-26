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

//Component Delays
const float reg_delays[6] 		= {2.616, 2.644, 2.879, 3.061, 3.602, 3.966};
const float add_delays[6] 		= {2.704, 3.713, 4.924, 5.638, 7.27, 9.566};
const float sub_delays[6] 		= {3.024, 3.412, 4.89, 5.569, 7.253, 9.566};
const float mul_delays[6] 		= {2.438, 3.651, 7.453, 7.811, 12.395, 15.354};
const float comp_delays[6] 		= {3.031, 3.934, 5.949, 6.256, 7.264, 8.416};
const float mux2x1_delays[6] 	= {4.083, 4.115, 4.815, 5.623, 8.079, 8.766};
const float shr_delays[6] 		= {3.644, 4.007, 5.178, 6.46, 8.819, 11.095};
const float shl_delays[6]		= {3.614, 3.98, 5.152, 6.549, 8.565, 11.22};
const float div_delays[6] 		= {0.619, 2.144, 15.439, 33.093, 86.312, 243.233};
const float mod_delays[6] 		= {0.758, 2.149, 16.078, 35.563, 88.142, 250.583};
const float inc_delays[6]		= {1.792, 2.218, 3.111, 3.471, 4.348, 6.2};
const float dec_delays[6]		= {1.792, 2.218, 3.108, 3.701, 4.685, 6.503};
#endif /* GLOBAL_H_ */
