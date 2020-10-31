/*
 * component.h
 *
 *  Created on: Oct 17, 2020
 *      Author: cwhos
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include "global.h"



component* CreateComponent(component_type type);

void UpdatePathDelay_Component(component* self, float path_delay_ns);
void UpdateComponentDelay(component* self);

uint8_t AddInputPort(component* self, net* input, port_type type);
uint8_t AddOutputPort(component* self, net* output, port_type type);


float GetComponentDelay(component* self);
component_type GetComponentType(component* self);
uint8_t GetComponentWidth(component* self);
uint8_t GetNumInputs(component* self);
uint8_t GetNumOutputs(component* self);
port GetInputPort(component* self, uint8_t idx);
port GetOutputPort(component* self, uint8_t idx);

void DestroyComponent(component* self);

#endif /* COMPONENT_H_ */
