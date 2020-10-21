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

int main(void) {
	SetLogFile("dpgen_log.txt");
	SetLogLevel(MESSAGE_LEVEL);

	LogMessage("dpgen started\r\n\0", MESSAGE_LEVEL);

	CloseLog();
	return EXIT_SUCCESS;
}
