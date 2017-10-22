/*
 * command_handler.h
 *
 *  Created on: 22.10.2017
 *      Author: Christoph
 */

#ifndef COMMAND_HANDLER_H_
#define COMMAND_HANDLER_H_

// receives USB packets and parses the commands


#include "packet_queue.h"


typedef struct {
    tPacketQueue *reply_queue;
    tPacketQueue command_queue;
} tCommandHandler;



void CommandHandlerInit(tCommandHandler *self);

void CommandHandlerMain(tCommandHandler *self);


#endif /* COMMAND_HANDLER_H_ */
