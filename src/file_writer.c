#include "file_writer.h"
#include "circuit.h"
#include "net.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void PrintFile(char* file_name, circuit* netlist_circuit) {

	FILE* fp;

	fp = fopen(file_name, "w");
	int num_in = netlist_circuit->num_inputs;
	int num_out = netlist_circuit->num_outputs;

	char in_list[num_in] = "";
	char out_list[num_out] = "";

	for (i = 0; i < num_in; i++) {
		strcat(in_list, netlist_circuit->input_nets[i]);
		if ((i + 1) != num_in) {
			strcat(in_list, ", "):
		}
	}

	for (j = 0; j < num_out; j++) {
		strcat(out_list, netlist_circuit->output_nets[j]);
		if ((j + 1) != num_out) {
			strcat(out_list, ", ");
		}
	}


	fputs("'timescale 1ns/1ps\n", fp);
	fprintf(fp, "module %s(Clk, Rst, %s %s)\n", netlist_circuit, in_list, out_list);
	fputs("\tinput Clk, Rst;", fp);
	fprintf(fp, "\tinput %s;\n", in_list);
	fprintf(fp, "\toutput %s;\n", out_list)
	



}

