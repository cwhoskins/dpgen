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

	fputs("'timescale 1ns/1ps\n", fp);
	fprintf(fp, "module %s(Clk, Rst, %s %s)\n", file_name, circuit->input_nets, circuit->output_nets);
	fputs("\tinput Clk, Rst;", fp);
	PrintNet(fp, netlist_circuit);
	



}

