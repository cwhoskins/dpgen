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



component* InitializeComponent(char* name, component_type type);
uint8_t SetInput(component* cur_component, net* input, uint8_t input_idx);
uint8_t SetOutput(component* cur_component, net* output, uint8_t output_idx);


#endif /* COMPONENT_H_ */
