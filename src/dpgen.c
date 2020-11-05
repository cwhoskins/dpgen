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

	char txt_file[64];
	char verilog_file[64];
	float delay = 0.0;

	if(argc < 3) {
		printf("ERROR: Not enough arguments.\n");
		return EXIT_FAILURE;
	}
	else if (argc > 3) {
		printf("ERROR: Too many arguments.\n");
		return EXIT_FAILURE;
	}
	else {
		strcpy(txt_file, argv[1]);
		strcpy(verilog_file, argv[2]);
	}


	SetLogFile("dpgen_log.txt");
	SetLogLevel(MESSAGE_LEVEL);
	LogMessage("dpgen started\r\n\0", MESSAGE_LEVEL);

	circuit* netlist_circuit = Circuit_Create();
	ReadNetlist("474a_circuit1.txt", netlist_circuit);
	//ReadNetlist(txt_file, netlist_circuit);
	PrintFile("output.txt", netlist_circuit);
	//PrintFile(verilog_file, netlist_circuit);

	delay = Circuit_GetCriticalPath(netlist_circuit);
	printf("Critical path: %0.3f ns", delay);

	CloseLog();
	return EXIT_SUCCESS;

	
}
