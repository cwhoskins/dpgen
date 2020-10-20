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

int main(void) {
	SetLogFile("dpgen_log.txt");
	SetLogLevel(0);

	LogMessage("dpgen started\r\n\0", 1);

	CloseLog();
	return EXIT_SUCCESS;
}
