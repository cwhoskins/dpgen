/*
 * net.h
 *
 *  Created on: Oct 17, 2020
 *      Author: cwhos
 */

#ifndef NET_H_
#define NET_H_

#include <stdint.h>
#include "global.h"

net* InitializeNet(char* name, net_type type, net_sign sign, uint8_t width);
net* FindNet(char* name);
uint8_t AddConnection(net* cur_net, component* connection);


#endif /* NET_H_ */
