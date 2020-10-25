/*
 * component.c
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */
#include <stdio.h>
#include <stdlib.h>
#include "component.h"
#include "net.h"

const uint8_t max_dp_inputs = 2;
const uint8_t max_ctrl_inputs = 1;
const uint8_t max_dp_outputs = 1;
const uint8_t max_ctrl_outputs = 3;

typedef struct struct_component {
	component_type type;
	float delay;
	net_sign sign;
	uint8_t width;

	uint8_t asap_time;
	uint8_t alap_time;

	uint8_t num_dp_inputs;
	uint8_t num_ctrl_inputs;
	uint8_t num_dp_outputs;
	uint8_t num_ctrl_outputs;
	net* dp_inputs[2];
	net* ctrl_input[1];
	net* dp_outputs[1];
	net* ctrl_outputs[3];

} component;

component* CreateComponent(component_type type) {
	uint8_t idx = 0;
	component* new_component = (component*) malloc(sizeof(component));
	if(NULL != new_component) {
		if(component_unknown != type) {
			new_component->type = type;
			new_component->width = 0;
			new_component->asap_time = 255;
			new_component->alap_time = 0;

			//Initialize all net links to NULL
			for(idx = 0; idx < max_dp_inputs; idx++) {
				new_component->dp_inputs[idx] = NULL;
			}
			for(idx = 0; idx < max_ctrl_inputs; idx++) {
				new_component->ctrl_input[idx] = NULL;
			}
			for(idx = 0; idx < max_dp_outputs; idx++) {
				new_component->dp_outputs[idx] = NULL;
			}
			for(idx = 0; idx < max_ctrl_outputs; idx++) {
				new_component->ctrl_outputs[idx] = NULL;
			}
			//Default to 2 DP inputs & no control
			new_component->num_ctrl_inputs = 0;
			new_component->num_dp_inputs = 2;
			new_component->num_ctrl_outputs = 0;
			new_component->num_dp_outputs = 1;

			switch(type) {
			case load_register:
				new_component->num_dp_inputs = 1;
				break;
			case mux2x1:
				new_component->num_ctrl_inputs = 1;
				break;
			case comparator:
				new_component->num_ctrl_outputs = 3;
				new_component->num_dp_outputs = 0;
				break;
			case shift_right:
				new_component->num_ctrl_inputs = 1;
				new_component->num_dp_inputs = 1;
				break;
			case shift_left:
				new_component->num_ctrl_inputs = 1;
				new_component->num_dp_inputs = 1;
				break;
			case incrementer:
				new_component->num_dp_inputs = 1;
				break;
			case decrementer:
				new_component->num_dp_inputs = 1;
				break;
			default:
				break;
			}
		}
	}
	return new_component;
}

uint8_t SetControlInput(component* self, net* ctrl_input, uint8_t ctrl_idx) {
	uint8_t ret_value = SUCCESS;
	if(NULL != self && NULL != ctrl_input) {
		if(ctrl_idx < self->num_ctrl_inputs) {
			self->ctrl_input[ctrl_idx] = ctrl_input;
			AddReceiver(ctrl_input, self);
		} else {
			ret_value = FAILURE;
		}
	} else {
		ret_value = FAILURE;
	}
	return ret_value;
}

uint8_t SetDatapathInput(component* self, net* dp_input, uint8_t dp_idx) {
	uint8_t ret_value = SUCCESS;
	if(NULL != self && NULL != dp_input) {
		if(dp_idx < self->num_dp_inputs) {
			self->dp_inputs[dp_idx] = dp_input;
			AddReceiver(dp_input, self);
			if(GetNetWidth(dp_input) > self->width && comparator == self->type) {
				self->width = GetNetWidth(dp_input);
			}
		} else {
			ret_value = FAILURE;
		}
	} else {
		ret_value = FAILURE;
	}
	return ret_value;
}

uint8_t SetDatapathOutput(component* self, net* output, uint8_t output_idx) {
	uint8_t ret_value = SUCCESS;
	if(NULL != self && NULL != output) {
		if(output_idx < self->num_dp_outputs) {
			self->dp_outputs[output_idx] = output;
			AddDriver(output, self);
			if(self->type != comparator) {
				self->width = GetNetWidth(output);
			}
		} else {
			ret_value = FAILURE;
		}
	} else {
		ret_value = FAILURE;
	}
	return ret_value;
}
uint8_t SetControlOutput(component* self, net* output, uint8_t output_idx) {
	uint8_t ret_value = SUCCESS;
	if(NULL != self && NULL != output) {
		if(output_idx < self->num_ctrl_outputs) {
			self->ctrl_outputs[output_idx] = output;
			AddDriver(output, self);
		} else {
			ret_value = FAILURE;
		}
	} else {
		ret_value = FAILURE;
	}
	return ret_value;
}
