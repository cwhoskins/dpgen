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
#include "logger.h"

typedef struct struct_net {
	net_type type;
	char name[64];
	uint8_t width;
	uint8_t is_scheduled;
	net_sign sign;
	component* driver;
	component** receivers;
	uint8_t num_receivers;
	float delay_ns;
} net;

const uint8_t max_receivers = 32;

net* Net_Create(char* name, net_type type, net_sign sign, uint8_t width) {

	net* new_net = (net*) malloc(sizeof(net));
	if(NULL != new_net) {
		strcpy(new_net->name, name);
		new_net->type = type;
		new_net->sign = sign;
		new_net->width = width;
		new_net->driver = NULL;
		new_net->delay_ns = -1.0f;
		new_net->num_receivers = 0;
		new_net->receivers = (component**) malloc(max_receivers * sizeof(component*));
		if(NULL == new_net->receivers) {
			Net_Destroy(new_net);
		}
	}
	return new_net;
}

void Net_ResetDelay(net* self) {
	if(NULL != self) {
		char log_msg[256];
		sprintf(log_msg,"MSG: Net %s Delay Reset\n", self->name);
		LogMessage(log_msg, MESSAGE_LEVEL);
		self->delay_ns = -1.0f;
	}
}

void Net_UpdatePathDelay(net* self, float path_delay_ns) {
	uint8_t idx;
	if(NULL != self) {
		if(path_delay_ns > self->delay_ns) {

			char log_msg[256];
			sprintf(log_msg,"MSG: Net %s delay set to %.2f ns\n", self->name, path_delay_ns);
			LogMessage(log_msg, MESSAGE_LEVEL);

			self->delay_ns = path_delay_ns;
			for(idx = 0; idx < self->num_receivers;idx++) {
				Component_UpdatePathDelay(self->receivers[idx], path_delay_ns);
			}
		}
	}
}

void Net_GetName(net* self, char* buffer) {
	if(NULL != self) {
		strcpy(buffer, self->name);
	}
	return;
}

net_type Net_GetType(net* self) {
	net_type cur_type = net_error;
	if(NULL != self) {
		cur_type = self->type;
	}
	return cur_type;
}

net_sign Net_GetSign(net* self) {
	net_sign cur_sign = sign_error;
	if(NULL != self) {
		cur_sign = self->sign;
	}
	return cur_sign;
}

float Net_GetDelay(net* self) {
	float delay = -1.0f;
	if(NULL != self) {
		delay = self->delay_ns;
	}
	return delay;
}

uint8_t Net_GetWidth(net* self) {
	uint8_t cur_width = 0;
	if(NULL != self) {
		cur_width = self->width;
	}
	return cur_width;
}

void Net_AddDriver(net* self, component* new_driver) {
	if(NULL != self && NULL != new_driver) {
		if(NULL == self->driver) {
			self->driver = new_driver;
		}
	}
}

void Net_AddReceiver(net* self, component* new_receiver) {
	if(NULL != self && NULL != new_receiver) {
		if(self->num_receivers < max_receivers) {
			self->receivers[self->num_receivers] = new_receiver;
			self->num_receivers++;
		}
	}
}

void Net_Destroy(net* self) {
	if(NULL != self) {
		free(self->receivers);
		free(self);
		self = NULL;
	}
}

void TestPrintNet() {
	char* name = "a";
	net_type type = net_input;
	net_sign sign = net_unsigned;
	uint8_t width = 8;

	net* test = Net_Create(name, type, sign, width);
	PrintNet(test);

	Net_Destroy(test);
	return;

}

void PrintNet(net* self) {

	net_type type = self->type;
	uint8_t net_width = self->width;
	char net_type_keyword[16];

	switch(type) {
	case net_input:
		strcpy(net_type_keyword, "input");
		break;
	case net_output:
		strcpy(net_type_keyword, "output reg");
		break;
	case net_wire:
		strcpy(net_type_keyword, "wire");
		break;
	case net_reg:
		strcpy(net_type_keyword, "reg");
		break;
	default:
		strcpy(net_type_keyword, "err");
		break;
	}

	printf("\t%s [%d:0] %s;\n", net_type_keyword, (net_width-1), self->name);

}
