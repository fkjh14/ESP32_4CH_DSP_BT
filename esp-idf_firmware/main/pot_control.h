#ifndef __POT_CONTROL_H__
#define __POT_CONTROL_H__

#include <stdint.h>

/**
 * @brief     Initialize potentiometer ADC and start reading task
 *            Uses GPIO 32 (ADC1_CHANNEL_4) for analog input
 */
void initPotentiometer();

/**
 * @brief     Get current potentiometer volume (0-127 for AVRCP)
 */
uint8_t getPotentiometerVolume();

#endif /* __POT_CONTROL_H__ */
