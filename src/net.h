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

net* CreateNet(char* name, net_type type, net_sign sign, uint8_t width);

void GetNetName(net* self, char* buffer);
net_type GetNetType(net* self);
net_sign GetNetSign(net* self);
uint8_t GetNetWidth(net* self);

void ScheduleNet(net* self, uint8_t is_scheduled);
void AddReceiver(net* self, component* new_receiver);
void AddDriver(net* self, component* new_driver);
void DestroyNet(net* self);


#endif /* NET_H_ */
