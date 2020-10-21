/*
 * netlist_reader.c
 *
 *  Created on: Oct 18, 2020
 *      Author: cwhos
 */

#include "netlist_reader.h"
#include "net.h"
#include "logger.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void ReadNetlist(char* file_name) {

	   FILE *fp;
	   char buff[255];
	   char* word;
	   fp = fopen("test.txt", "r");
	   if(NULL == fp) {
		   printf("Error: File Open\r\n");
		   return;
	   }

	   char* fget_rtn = fgets(&buff[0], 250, fp);
	   if(NULL != fget_rtn) {
		   word = strtok(buff," ,");
		   while(NULL != word) {

		   }
	   }

	   fclose(fp);
}

void ParseAssignmentLine(char* line) {
	//Determine inputs, outputs, and component type
}

void ParseDeclarationLine(char* line) {
	//Determine width, net type, names
	char* word;
	net_type declare_type;
	uint8_t declare_width;
	net_sign declare_sign;
	//Get Declaration Type (i.e. reg, wire, input, output)
	word = strtok (line," ,");

	if(0 == strcmp(word, "input\0")) {
		declare_type = net_input;
	} else if(0 == strcmp(word, "output\0")) {
		declare_type = net_output;
	} else if(0 == strcmp(word, "wire\0")) {
		declare_type = net_wire;
	} else if(0 == strcmp(word, "reg\0")) {
		declare_type = net_reg;
	} else {
		//Error
	}

	//Determine Declaration sign
	word = strtok (NULL," ,");
	if(0 > strcmp(word, "UINT1\0")) { //Signed
		declare_sign = net_signed;
	} else { //Unsigned
		declare_sign = net_unsigned;
	}

	//Determine Declaration Width
	if(0 == strcmp(word, "INT1\0") || 0 == strcmp(word, "UINT1\0")) {
		declare_width = 1;
	} else if(0 == strcmp(word, "INT2\0") || 0 == strcmp(word, "UINT2\0")) {
		declare_width = 2;
	} else if(0 == strcmp(word, "INT8\0") || 0 == strcmp(word, "UINT8\0")) {
		declare_width = 8;
	}  else if(0 == strcmp(word, "INT16\0") || 0 == strcmp(word, "UINT16\0")) {
		declare_width = 16;
	}  else if(0 == strcmp(word, "INT32\0") || 0 == strcmp(word, "UINT32\0")) {
		declare_width = 32;
	}  else if(0 == strcmp(word, "INT64\0") || 0 == strcmp(word, "UINT64\0")) {
		declare_width = 64;
	} else { //Error

	}

	//Get all variable declarations in current line
	word = strtok (NULL," ,");
	while(NULL != word) {
		if(NULL != FindNet(word)) { //Declared Variable already exists
			LogMessage("ERROR: Variable redefined", ERROR_LEVEL);
			break;
		}
		InitializeNet(word, declare_type, declare_width, declare_sign);
		word = strtok (NULL," ,");
	}

}

void ParseNetlistLine(char* line) {

	char* word;
	word_class word_type;
	line_class line_type;

	if(NULL != line) {
	   word = strtok (line," ,");

	   //First Word determines reading behavior
	   word_type = CheckWordType(word); //Determine what type of word is (Variable, Net Declarative, Component Declarative, Width Declarative)
	   switch(word_type) {
	   case VARIABLE:
		   //If var exists, assignment, otherwise error
//		   if(NULL != FindNet(word) {
//			   line_type = ASSIGNMENT;
//			   ParseAssignmentLine(line);
//		   } else {
//			   line_type = ERROR;
//		   }
		   break;
	   case NET_DECLARATION:
		   line_type = NET_DECLARE;
		   ParseDeclarationLine(line);
		   break;
	   case COMMENT: //Line can be ignored
		   line_type = COMMENT;
		   return;
		   break;
	   default:
		   line_type = ERROR; //Error
		   break;
	   }
	}
}

word_class CheckWordType(char* word) {
	return WORD_ERROR;
}
