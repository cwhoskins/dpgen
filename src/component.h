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
float GetComponentDelay(component* self);
component_type GetComponentType(component* self);
uint8_t SetControlInput(component* self, net* ctrl_input, uint8_t ctrl_idx);
uint8_t SetDatapathInput(component* self, net* dp_input, uint8_t dp_idx);
uint8_t SetDatapathOutput(component* self, net* output, uint8_t output_idx);
uint8_t SetControlOutput(component* self, net* output, uint8_t output_idx);
void UpdateComponentDelay(component* self);
void DestroyComponent(component* self);

#endif /* COMPONENT_H_ */
