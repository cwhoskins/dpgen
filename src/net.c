/*
 * net.c
 *
 *  Created on: Oct 18, 2020
 *      Author: cwhos
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "net.h"
#include "component.h"


typedef struct struct_net {
	net_type type;
	char name[64];
	uint8_t width;
	uint8_t is_scheduled;
	net_sign sign;
	component* driver;
	component** receivers;
	uint8_t num_receivers;
} net;

const uint8_t max_receivers = 32;

net* CreateNet(char* name, net_type type, net_sign sign, uint8_t width) {

	net* new_net = (net*) malloc(sizeof(net));
	if(NULL != new_net) {
		strcpy(new_net->name, name);
		new_net->type = type;
		new_net->sign = sign;
		new_net->width = width;
		new_net->driver = NULL;
		new_net->num_receivers = 0;
		new_net->receivers = (component**) malloc(max_receivers * sizeof(component*));
		if(NULL == new_net->receivers) {
			DestroyNet(new_net);
		}
	}
	return new_net;
}
void GetNetName(net* self, char* buffer) {
	if(NULL != self) {
		strcpy(buffer, self->name);
	}
	return;
}

net_type GetNetType(net* self) {
	net_type cur_type = net_error;
	if(NULL != self) {
		cur_type = self->type;
	}
	return cur_type;
}

net_sign GetNetSign(net* self) {
	net_sign cur_sign = sign_error;
	if(NULL != self) {
		cur_sign = self->sign;
	}
	return cur_sign;
}

uint8_t GetNetWidth(net* self) {
	uint8_t cur_width = 0;
	if(NULL != self) {
		cur_width = self->width;
	}
	return cur_width;
}

void ScheduleNet(net* self, uint8_t is_scheduled) {

}

void AddDriver(net* self, component* new_driver) {
	if(NULL != self && NULL != new_driver) {
		if(NULL == self->driver) {
			self->driver = new_driver;
		}
	}
}

void AddReceiver(net* self, component* new_receiver) {
	if(NULL != self && NULL != new_receiver) {
		if(self->num_receivers < max_receivers) {
			self->receivers[self->num_receivers] = new_receiver;
			self->num_receivers++;
		}
	}
}

void DestroyNet(net* self) {
	free(self->driver);
	free(self->receivers);
	free(self);
	self = NULL;
}
