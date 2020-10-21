/*
 * net.c
 *
 *  Created on: Oct 18, 2020
 *      Author: cwhos
 */


#include "net.h"
#include "component.h"


typedef struct struct_net {
	net_type type;
	char* name;
	uint8_t width;
	net_sign sign;
	component* driver;
	component* receivers;
} net;


//net* InitializeNet(char* name, net_type type, net_sign sign, uint8_t width) {
//	return NULL;
//}
