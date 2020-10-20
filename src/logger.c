/*
 * logger.c
 *
 *  Created on: Oct 18, 2020
 *      Author: cwhos
 */
#include <stdio.h>
#include "logger.h"

typedef struct struct_logger {
	FILE* log_file;
	uint8_t minimum_log_level;
} logger;

logger log;

void SetLogFile(char* file_path) {

	log.log_file = fopen(file_path, "w+");
	if(NULL == log.log_file) {
	   printf("Error: Logging Failure\r\n\0");
	   return;
	}
}
void SetLogLevel(uint8_t level) {
	log.minimum_log_level = level;
}
void LogMessage(char* message, uint8_t level) {
	if(level >= log.minimum_log_level) {
		fprintf(log.log_file, message);
	}
}

void CloseLog() {
	fclose(log.log_file);
}
