/*
 * circuit.h
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_


#include "global.h"

net* FindNet(char* name);
void InitializeNet(char* name, net_type type, uint8_t width, net_sign sign);

#endif /* CIRCUIT_H_ */
