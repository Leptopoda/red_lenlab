/*
 * Lenlab, an oscilloscope software for the TI LaunchPad EK-TM4C123GXL
 * Copyright (C) 2017-2020 Christoph Simon and the Lenlab developer team
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include "logger.h"

#include "lenlab_protocol.h"
#include "reply_handler.h"


void
ADC0SS1Handler(void)
{
    tLogSeq *self = &logger.seq_group.log_seq[0];

    LogSeqIntHandler(self);
}


void
ADC1SS1Handler(void)
{
    tLogSeq *self = &logger.seq_group.log_seq[1];

    LogSeqIntHandler(self);
}


tError
LoggerStart(tLogger *self, uint32_t interval)
{
    if (self->lock) return LOCK_ERROR;

    if (adc_group.lock) return ADC_ERROR;

    ADCGroupSetHardwareOversample(&adc_group, 1);

    LogSeqGroupEnable(&self->seq_group, interval);

    ADCGroupLock(&adc_group);

    self->lock = true;

    return OK;
}


tError
LoggerStop(tLogger *self)
{
    if (!self->lock) return LOCK_ERROR;

    LogSeqGroupDisable(&self->seq_group);

    self->lock = false;

    ADCGroupUnlock(&adc_group);

    return OK;
}


void
LoggerMain(tLogger *self)
{
    uint32_t size;
    tEvent *reply;

    if (!self->lock) return;

    if (LogSeqGroupError(&self->seq_group)) {

        LoggerStop(self);

        ASSERT(0); // TODO Logger error handling in release build

    }
    else if (LogSeqGroupReady(&self->seq_group)) {

        //DEBUG_PRINT("LoggerData");

        reply = QueueAcquire(&reply_handler.reply_queue);

        EventSetReply(reply, LoggerData);
        EventSetType(reply, IntArray);

        size = sizeof(uint32_t) * 2 * ADC_GROUP_SIZE; // bytes; two channels per ADC
        ASSERT(size <= LENLAB_PACKET_BODY_LENGTH);
        EventSetBodyLength(reply, size);

        size = LogSeqGroupDataGet(&self->seq_group, (uint32_t *) (EventGetBody(reply)));
        ASSERT(size == 2 * ADC_GROUP_SIZE); // number of samples

        QueueWrite(&reply_handler.reply_queue);

        LogSeqGroupRelease(&self->seq_group);

    }
}


void
LoggerInit(tLogger *self)
{
    LogSeqGroupInit(&self->seq_group);
}
