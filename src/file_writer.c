#include "file_writer.h"
#include "circuit.h"
#include "net.h"
#include "component.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


void PrintFile(char* file_name, circuit* circ) {

//	FILE* fp;
//	int i = 0;
//
//	fp = fopen(file_name, "w+");
//
//
//	fputs("'timescale 1ns/1ps\n", fp);
//	fprintf(fp, "module %s(Clk, Rst, %s %s)\n", file_name, circ->input_nets, circ->output_nets);
//	fputs("\tinput Clk, Rst;", fp);
//
//	for (i = 0; i < circ->num_nets; i++) {
//		PrintNet(fp, circ->netlist[i]);
//	}
	


	return;
}

void DeclareNet(net* self, char* line_buffer) {

	net_type type = GetNetType(self);
	uint8_t net_width = GetNetWidth(self);
	char net_type_keyword[16];
	char net_name[64];
	GetNetName(self, net_name);

	switch(type) {
	case net_input:
		strcpy(net_type_keyword, "input");
		break;
	case net_output:
		strcpy(net_type_keyword, "output reg");
		break;
	case net_wire:
		strcpy(net_type_keyword, "wire");
		break;
	case net_reg:
		strcpy(net_type_keyword, "reg");
		break;
	default:
		strcpy(net_type_keyword, "err");
		break;
	}

	sprintf(line_buffer, "\t%s [%d:0] %s;\n", net_type_keyword, (net_width-1), net_name);

}

void DeclareComponent(component* self, char* line_buffer) {
	component_type type;
	uint8_t width;
	uint8_t io_idx, num_ports;
	port temp_port;
	char type_declaration[32];
	char component_name[64];
	char port_declaration[512] = "";
	char temp_port_declaration[64];
	char port_name[32];

	if(NULL != self) {
		num_ports = GetNumOutputs(self) + GetNumInputs(self);
		for(io_idx = 0; io_idx < num_ports; io_idx++) {

			if(io_idx < GetNumInputs(self)) {
				temp_port = GetInputPort(self, io_idx);
			} else {
				temp_port = GetOutputPort(self, (io_idx - GetNumInputs(self)));
			}

			GetNetName(temp_port.port_net, port_name);
			switch(temp_port.type) {
			case datapath_a:
				sprintf(temp_port_declaration, ".a(%s)", port_name);
				break;
			case datapath_b:
				sprintf(temp_port_declaration, ".b(%s)", port_name);
				break;
			case datapath_out:
				sprintf(temp_port_declaration, ".o(%s)", port_name);
				break;
			case mux_sel:
				sprintf(temp_port_declaration, ".sel(%s)", port_name);
				break;
			case shift_amount:
				sprintf(temp_port_declaration, ".sh_amt(%s)", port_name);
				break;
			case greater_than_out:
				sprintf(temp_port_declaration, ".gt(%s)", port_name);
				break;
			case less_than_out:
				sprintf(temp_port_declaration, ".lt(%s)", port_name);
				break;
			case equal_out:
				sprintf(temp_port_declaration, ".eq(%s)", port_name);
				break;
			default:
				break;
			}
			strcat(port_declaration, temp_port_declaration);
		}

		width = GetComponentWidth(self);

		type = GetComponentType(self);

		switch(type) {
		case load_register:
			strcpy(type_declaration, "Reg");
			break;
		case adder:
			strcpy(type_declaration, "Add");
			break;
		case subtractor:
			strcpy(type_declaration, "Sub");
			break;
		case multiplier:
			strcpy(type_declaration, "Mul");
			break;
		case divider:
			strcpy(type_declaration, "Div");
			break;
		case modulo:
			strcpy(type_declaration, "Mod");
			break;
		case mux2x1:
			strcpy(type_declaration, "Mux2x1");
			break;
		case comparator:
			strcpy(type_declaration, "Comp");
			break;
		case shift_right:
			strcpy(type_declaration, "SHR");
			break;
		case shift_left:
			strcpy(type_declaration, "SHL");
			break;
		case incrementer:
			strcpy(type_declaration, "Inc");
			break;
		case decrementer:
			strcpy(type_declaration, "Dec");
			break;
		default:
			break;
		}
	}



    printf("%s #(.DATA_WIDTH(%d)) %s (%s);", type_declaration, width, component_name, port_declaration);
}
