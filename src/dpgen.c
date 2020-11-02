/*
 ============================================================================
 Name        : dpgen.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "global.h"
#include "netlist_reader.h"
#include "circuit.h"
#include "net.h"
#include "file_writer.h"

int main(int argc, char *argv[]) {
	SetLogFile("dpgen_log.txt");
	SetLogLevel(MESSAGE_LEVEL);
	LogMessage("dpgen started\r\n\0", MESSAGE_LEVEL);

	circuit* netlist_circuit = Circuit_Create();
	ReadNetlist("474a_circuit1.txt", netlist_circuit);
	PrintFile("output.txt", netlist_circuit);

	CloseLog();
	return EXIT_SUCCESS;

	/*
	if(argc < 3) {
		printf("ERROR: Not enough arguments\n");
		return;
	}
	else if (argc > 3) {
		printf("ERROR: Too many arguments\n");
		return;
	}
	else {
		txt_file = argv[1];
		verilog_file = argv[2];
	}
	

	PrintFile(verilog_file, CIRCUIT);
	*/
	
}
