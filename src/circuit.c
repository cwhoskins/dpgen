/*
 * circuit.c
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */

#include "circuit.h"
#include <stddef.h>

typedef struct struct_circuit {
	net** input_nets;
	net** netlist;
	uint8_t num_nets;
} circuit;

circuit* CreateCircuit() {
	const uint8_t max_inputs = 32;
	const uint8_t max_nets = 32;
	circuit* new_circuit = (circuit*) malloc(sizeof(circuit));
	if(NULL != new_circuit) {
		new_circuit->num_nets = 0;
		new_circuit->input_nets = (net**) malloc(max_inputs * sizeof(net*));
		new_circuit->netlist = (net**) malloc(max_nets * sizeof(net*));
	}
	if(NULL == new_circuit->input_nets || NULL == new_circuit->netlist) {
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
	if(NULL != new_net) {
		self->netlist[self->num_nets] = new_net;
		self->num_nets++;
	}
	return;
}

void DestroyCircuit(circuit* self) {
	uint8_t net_idx = 0;
	while(net_idx < self->num_nets) {
		DestroyNet(self->netlist[net_idx]);
		net_idx++;
	}
	free(self->input_nets);
	free(self->netlist);
	free(self);
	self = NULL;
}
