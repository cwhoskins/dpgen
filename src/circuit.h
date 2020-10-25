/*
 * circuit.h
 *
 *  Created on: Oct 20, 2020
 *      Author: cwhos
 */

#ifndef CIRCUIT_H_
#define CIRCUIT_H_


#include "global.h"

circuit* CreateCircuit();
net* FindNet(circuit* self, char* name);
void AddNet(circuit* self, net* new_net);
void ScheduleASAP(circuit* self);
void ScheduleALAP(circuit* self);
void DestroyCircuit(circuit* self);

#endif /* CIRCUIT_H_ */
