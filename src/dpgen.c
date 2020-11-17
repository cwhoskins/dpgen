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

#if DEBUG_MODE == 1

	SetLogFile(NULL);
	SetLogLevel(CIRCUIT_ERROR_LEVEL);
	LogMessage("dpgen started - DEBUG\n", MESSAGE_LEVEL);

	uint8_t num_tests = 16;
	uint8_t idx;
	circuit* netlist_circuit = NULL;
	char output_file[64];
	char input_file[64];
	char log_msg[128];
	float delay;

	for(idx = 0; idx < num_tests; idx++) {
		sprintf(log_msg, "\nMSG: Testing Circuit #%d\n", (idx+1));
		LogMessage(log_msg, MESSAGE_LEVEL);
		sprintf(input_file, "./circuits/%d.txt", (idx+1));
		sprintf(output_file, "./outputs/%d.v", (idx+1));

		netlist_circuit = Circuit_Create();
		if(NULL == netlist_circuit) {
			LogMessage("ERROR: Failure to create circuit object\n", ERROR_LEVEL);
			return FAILURE;
		}
		if(SUCCESS == ReadNetlist(input_file, netlist_circuit)) {
			Circuit_CalculateDelay(netlist_circuit);
			delay = Circuit_GetCriticalPath(netlist_circuit);
			printf("Critical path #%d: %0.3f ns\n", (idx+1), delay);
			PrintFile(output_file, netlist_circuit);
		} else {
			LogMessage("ERROR: Could not parse input\n", ERROR_LEVEL);
		}

		Circuit_Destroy(netlist_circuit);
	}

	CloseLog();

	return SUCCESS;

#else
	char* txt_file = NULL;
	char* verilog_file = NULL;
	float delay = -1;

	if(argc < 3) {
		printf("ERROR: Not enough arguments.\n");
		return FAILURE;
	}
	else if (argc > 3) {
		printf("ERROR: Too many arguments.\n");
		return FAILURE;
	}
	else {
		txt_file = argv[1];
		verilog_file = argv[2];
	}


	SetLogFile(NULL);
	SetLogLevel(CIRCUIT_ERROR_LEVEL);
	LogMessage("dpgen started\n\0", MESSAGE_LEVEL);

	circuit* netlist_circuit = Circuit_Create();
	if(FAILURE == ReadNetlist(txt_file, netlist_circuit)) {
		Circuit_Destroy(netlist_circuit);
		return EXIT_FAILURE;
	}
	PrintFile(verilog_file, netlist_circuit);

	Circuit_CalculateDelay(netlist_circuit);
	delay = Circuit_GetCriticalPath(netlist_circuit);
	printf("Critical path: %0.3f ns\n", delay);

	CloseLog();
	Circuit_Destroy(netlist_circuit);

	return EXIT_SUCCESS;
#endif
	
}
