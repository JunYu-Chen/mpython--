/*
 Arduino.h - Main include file for the Arduino SDK
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef MAIN_ESP32_HAL_ADC_H_
#define MAIN_ESP32_HAL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "esp32-hal.h"

typedef enum {
    ADC_0db,
    ADC_2_5db,
    ADC_6db,
    ADC_11db
} adc_attenuation_t;

/*
 * Get ADC value for pin
 * */
uint16_t analogRead(uint8_t pin);
void analogWrite(uint8_t pin, uint16_t val);

/*
 * Set the resolution of analogRead return values. Default is 12 bits (range from 0 to 4096).
 * If between 9 and 12, it will equal the set hardware resolution, else value will be shifted.
 * Range is 1 - 16
 *
 * Note: compatibility with Arduino SAM
 */
void analogReadResolution(uint8_t bits);

/*
 * Sets the sample bits and read resolution
 * Default is 12bit (0 - 4095)
 * Range is 9 - 12
 * */
void analogSetWidth(uint8_t bits);

/*
 * Set number of cycles per sample
 * Default is 8 and seems to do well
 * Range is 1 - 255
 * */
void analogSetCycles(uint8_t cycles);

/*
 * Set number of samples in the range.
 * Default is 1
 * Range is 1 - 255
 * This setting splits the range into
 * "samples" pieces, which could look
 * like the sensitivity has been multiplied
 * that many times
 * */
void analogSetSamples(uint8_t samples);

/*
 * Set the divider for the ADC clock.
 * Default is 1
 * Range is 1 - 255
 * */
void analogSetClockDiv(uint8_t clockDiv);

/*
 * Set the attenuation for all channels
 * Default is 11db
 * */
void analogSetAttenuation(adc_attenuation_t attenuation);

/*
 * Set the attenuation for particular pin
 * Default is 11db
 * */
void analogSetPinAttenuation(uint8_t pin, adc_attenuation_t attenuation);

/*
 * Get value for HALL sensor (without LNA)
 * connected to pins 36(SVP) and 39(SVN)
 * */
int hallRead();

/*
 * Non-Blocking API (almost)
 *
 * Note: ADC conversion can run only for single pin at a time.
 *       That means that if you want to run ADC on two pins on the same bus,
 *       you need to run them one after another. Probably the best use would be
 *       to start conversion on both buses in parallel.
 * */

/*
 * Attach pin to ADC (will also clear any other analog mode that could be on)
 * */
bool adcAttachPin(uint8_t pin);

/*
 * Start ADC conversion on attached pin's bus
 * */
bool adcStart(uint8_t pin);

/*
 * Check if conversion on the pin's ADC bus is currently running
 * */
bool adcBusy(uint8_t pin);

/*
 * Get the result of the conversion (will wait if it have not finished)
 * */
uint16_t adcEnd(uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_ESP32_HAL_ADC_H_ */
