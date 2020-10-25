/*
 * circuit.c
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */

#include "circuit.h"
#include "net.h"
#include "component.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct struct_circuit {
	net** input_nets;
	net** output_nets;
	net** netlist;
	component** component_list;

	uint8_t num_nets;
	uint8_t num_inputs;
	uint8_t num_outputs;
	uint8_t num_components;
} circuit;

circuit* CreateCircuit() {
	const uint8_t max_inputs = 32;
	const uint8_t max_nets = 32;
	circuit* new_circuit = (circuit*) malloc(sizeof(circuit));
	if(NULL != new_circuit) {
		new_circuit->num_nets = 0;
		new_circuit->num_inputs = 0;
		new_circuit->num_outputs = 0;
		new_circuit->input_nets = (net**) malloc(max_inputs * sizeof(net*));
		new_circuit->netlist = (net**) malloc(max_nets * sizeof(net*));
		new_circuit->output_nets = (net**) malloc(max_nets * sizeof(net*));
	}
	if(NULL == new_circuit->input_nets || NULL == new_circuit->netlist || NULL == new_circuit->output_nets || NULL == new_circuit->component_list) {
		DestroyCircuit(new_circuit);
	}
	return new_circuit;
}

net* FindNet(circuit* self, char* name) {
	uint8_t net_idx = 0;
	net* return_net = NULL;
	char node_name[64];
	while(net_idx < self->num_nets) {
		GetNetName(self->netlist[net_idx], node_name);
		if(0 == strcmp(node_name, name)) {
			return_net = self->netlist[net_idx];
			break;
		}
		net_idx++;
	}
	return return_net;
}

void AddNet(circuit* self, net* new_net) {
	if(NULL != new_net && NULL != self) {
		self->netlist[self->num_nets] = new_net;
		if(net_output == GetNetType(new_net)) {
			self->output_nets[self->num_outputs] = new_net;
			self->num_outputs++;
		} else if(net_input == GetNetType(new_net)) {
			self->input_nets[self->num_inputs] = new_net;
			self->num_inputs++;
		}
		self->num_nets++;
	}
	return;
}

void ScheduleComponentASAP(circuit* self, component* scheduled_comp, uint8_t timeslot) {

}

void ScheduleASAP(circuit* self) {
	uint8_t idx, rx_idx;

	//Reset netlist for new scheduling
	for(idx = 0; idx < self->num_nets;idx++) {
		if(net_input != GetNetType(self->netlist[idx])) {
			ScheduleNet(self->netlist[idx], FALSE);
		} else {
			ScheduleNet(self->netlist[idx], TRUE);
		}
	}

}

void ScheduleALAP(circuit* self) {

}

void DestroyCircuit(circuit* self) {
	uint8_t net_idx = 0;
	while(net_idx < self->num_nets) {
		DestroyNet(self->netlist[net_idx]);
		net_idx++;
	}
	free(self->output_nets);
	free(self->input_nets);
	free(self->netlist);
	free(self);
	self = NULL;
}
