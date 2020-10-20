/*
 * net.h
 *
 *  Created on: Oct 17, 2020
 *      Author: cwhos
 */

#ifndef NET_H_
#define NET_H_

#include <stdint.h>
#include "component.h"


typedef enum enum_net_type {
	net_wire,
	net_reg,
	net_input,
	net_output
} net_type;

typedef enum {
	net_signed,
	net_unsigned
} net_sign;

//typedef struct struct_net {
//	net_type type;
//	char* name;
//	uint8_t width;
//	net_sign sign;
//	component* connections;
//} net;
//
//net* InitializeNet(char* name, net_type type, net_sign sign, uint8_t width);
//net* FindNet(char* name);
//uint8_t AddConnection(net* cur_net, component* connection);


#endif /* NET_H_ */
