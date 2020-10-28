#include "file_writer.h"
#include "circuit.h"
#include "net.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


void PrintFile(char* file_name, circuit* circ) {

	FILE* fp;
	int i = 0;

	fp = fopen(file_name, "w");

	/*
	fputs("'timescale 1ns/1ps\n", fp);
	fprintf(fp, "module %s(Clk, Rst, %s %s)\n", file_name, circ->input_nets, circ->output_nets);
	fputs("\tinput Clk, Rst;", fp);

	for (i = 0; i < circ->num_nets; i++) {
		PrintNet(fp, circ->netlist[i]);
	}
	*/
	


	return;
}

