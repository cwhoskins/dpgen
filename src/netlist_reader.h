/*
 * netlist_reader.h
 *
 *  Created on: Oct 18, 2020
 *      Author: cwhos
 */

#ifndef NETLIST_READER_H_
#define NETLIST_READER_H_

#include "global.h"

uint8_t ReadNetlist(char* file_name, circuit* netlist_circuit);
static uint8_t ParseNetlistLine(char* line, circuit* netlist_circuit);
static uint8_t ParseAssignmentLine(char* first_word, circuit* netlist_circuit);
static uint8_t ParseDeclarationLine(char* first_word, circuit* netlist_circuit);

word_class CheckWordType(char* word);
component_type ReadComponentType(char* word);
uint8_t ReadNetWidth(char* word);
net_type ReadNetType(char* word);
net_sign ReadNetSign(char* word);

void TestNetlistReader();
void TestLineParsing();

#endif /* NETLIST_READER_H_ */
