/*
 * oscilloscope.h
 *

Lenlab, an oscilloscope software for the TI LaunchPad EK-TM4C123GXL
Copyright (C) 2017 Christoph Simon and the Lenlab developer team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef OSCILLOSCOPE_H_
#define OSCILLOSCOPE_H_


#define OSCILLOSCOPE_HEADER_LENGTH 8
#define OSCILLOSCOPE_FILTER_LENGTH 8


typedef struct Oscilloscope {
    bool active;
    uint8_t count;
    uint16_t filter[OSCILLOSCOPE_FILTER_LENGTH];
    uint16_t filter_index;
    uint16_t filter_state;
    bool trigger_wait;
    bool trigger_active;
    bool trigger_save;
    uint8_t trigger_post_count;
} tOscilloscope;


extern tOscilloscope oscilloscope;

void OscilloscopeSetSamplerateDivider(tOscilloscope *self, uint8_t divider);

void OscilloscopeStart(tOscilloscope *self);

void OscilloscopeMain(tOscilloscope *self);

void OscilloscopeInit(tOscilloscope *self);


#endif /* OSCILLOSCOPE_H_ */
