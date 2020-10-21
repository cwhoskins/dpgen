/*
 * netlist_reader.h
 *
 *  Created on: Oct 18, 2020
 *      Author: cwhos
 */

#ifndef NETLIST_READER_H_
#define NETLIST_READER_H_

#include "global.h"

void ReadNetlist(char* file_name);
void ParseNetlistLine(char* line);
void ParseAssignmentLine(char* line);
void ParseDeclarationLine(char* line);
word_class CheckWordType(char* word);

#endif /* NETLIST_READER_H_ */
