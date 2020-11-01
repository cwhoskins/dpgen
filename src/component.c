/*
 * component.c
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */
#include <stdio.h>
#include <stdlib.h>
#include "component.h"
#include "logger.h"
#include "net.h"

const uint8_t max_dp_inputs = 2;
const uint8_t max_ctrl_inputs = 1;
const uint8_t max_dp_outputs = 1;
const uint8_t max_ctrl_outputs = 3;

typedef struct struct_component {
	component_type type;
	float delay_ns;
	net_sign sign;
	uint8_t width;

	port input_ports[8];
	port output_ports[8];
	uint8_t num_inputs;
	uint8_t num_outputs;

} component;

component* Component_Create(component_type type) {
	component* new_component = (component*) malloc(sizeof(component));
	if(NULL != new_component) {
		if(component_unknown != type) {
			new_component->type = type;
			new_component->width = 0;
			new_component->delay_ns = 0.0f;
			new_component->sign = net_unsigned;
			new_component->num_inputs = 0;
			new_component->num_outputs = 0;
		}
	}
	return new_component;
}

void Component_UpdatePathDelay(component* self, float path_delay_ns) {
	uint8_t output_idx;
	float new_delay_ns;
	if(load_register == self->type) {
		new_delay_ns = self->delay_ns;
	} else {
		new_delay_ns = path_delay_ns + self->delay_ns;
	}
	if(NULL != self) {
		for(output_idx = 0; output_idx < self->num_outputs; output_idx++) {
			Net_UpdatePathDelay(self->output_ports[output_idx].port_net, new_delay_ns);
		}
	}
}

uint8_t Component_AddInputPort(component* self, net* input, port_type type) {
	uint8_t ret_value = SUCCESS;
	if(NULL != self && NULL != input) {
		if(8 > self->num_inputs) {
			self->input_ports[self->num_inputs].port_net = input;
			self->input_ports[self->num_inputs].type = type;
			self->num_inputs++;
			Net_AddReceiver(input, self);
			if(datapath_a == type || datapath_b == type) {
				if(net_signed == Net_GetSign(input)) {
					self->sign = net_signed;
				}
			}
			if(Net_GetWidth(input) > self->width && comparator == self->type) {
				self->width = Net_GetWidth(input);
			}
		} else {
			ret_value = FAILURE;
		}
	} else {
		ret_value = FAILURE;
	}
	return ret_value;
}

uint8_t Component_AddOutputPort(component* self, net* output, port_type type) {
	uint8_t ret_value = SUCCESS;
	if(NULL != self && NULL != output) {
		if(8 > self->num_outputs) {
			self->output_ports[self->num_outputs].port_net = output;
			self->output_ports[self->num_outputs].type = type;
			self->num_outputs++;
			Net_AddDriver(output, self);
			if(datapath_out == type) {
				if(net_signed == Net_GetSign(output)) {
					self->sign = net_signed;
				}
			}
			if(self->type != comparator) {
				self->width = Net_GetWidth(output);

			}
		} else {
			ret_value = FAILURE;
		}
	} else {
		ret_value = FAILURE;
	}
	return ret_value;
}

port Component_GetInputPort(component* self, uint8_t idx) {
	port ret_value;
	ret_value.port_net = NULL;
	ret_value.type = port_error;
	if(NULL != self) {
		if(idx < self->num_inputs) ret_value = self->input_ports[idx];
	}
	return ret_value;
}

port Component_GetOutputPort(component* self, uint8_t idx) {
	port ret_value;
	ret_value.port_net = NULL;
	ret_value.type = port_error;
	if(NULL != self) {
		if(idx < self->num_outputs) ret_value = self->output_ports[idx];
	}
	return ret_value;
}

uint8_t Component_GetNumInputs(component* self) {
	uint8_t ret_value = 0;
	if(NULL != self) {
		ret_value = self->num_inputs;
	}
	return ret_value;
}

uint8_t Component_GetNumOutputs(component* self) {
	uint8_t ret_value = 0;
	if(NULL != self) {
		ret_value = self->num_outputs;
	}
	return ret_value;
}


void Component_UpdateDelay(component* self) {
	uint8_t width_idx;
	if(NULL != self) {
		switch(self->width) {
		case 1:
			width_idx = 0;
			break;
		case 2:
			width_idx = 1;
			break;
		case 8:
			width_idx = 2;
			break;
		case 16:
			width_idx = 3;
			break;
		case 32:
			width_idx = 4;
			break;
		case 64:
			width_idx = 5;
			break;
		default:
			LogMessage("ERROR: Incorrect Component Width\r\n", ERROR_LEVEL);
			return;
			break;
		}
		switch(self->type) {
		case load_register:
			self->delay_ns = reg_delays[width_idx];
			break;
		case adder:
			self->delay_ns = add_delays[width_idx];
			break;
		case subtractor:
			self->delay_ns = sub_delays[width_idx];
			break;
		case multiplier:
			self->delay_ns = mul_delays[width_idx];
			break;
		case divider:
			self->delay_ns = div_delays[width_idx];
			break;
		case modulo:
			self->delay_ns = mod_delays[width_idx];
			break;
		case mux2x1:
			self->delay_ns = mux2x1_delays[width_idx];
			break;
		case comparator:
			self->delay_ns = comp_delays[width_idx];
			break;
		case shift_right:
			self->delay_ns = shr_delays[width_idx];
			break;
		case shift_left:
			self->delay_ns = shl_delays[width_idx];
			break;
		case incrementer:
			self->delay_ns = inc_delays[width_idx];
			break;
		case decrementer:
			self->delay_ns = dec_delays[width_idx];
			break;
		default:
			break;
		}
	}
}

component_type Component_GetType(component* self) {
	component_type type = component_unknown;
	if(NULL != self) {
		type = self->type;
	}
	return type;
}

uint8_t Component_GetWidth(component* self) {
	uint8_t width = 0;
	if(NULL != self) {
		width = self->width;
	}
	return width;
}

void Component_Destroy(component* self) {
	if(NULL != self) {
		free(self);
		self = NULL;
	}
}
