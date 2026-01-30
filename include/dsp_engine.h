#ifndef DSP_ENGINE_H
#define DSP_ENGINE_H

#include <stdint.h>

void apply_low_pass(const int16_t* input, int16_t* output, uint32_t length);

void apply_gain(int16_t* data, uint32_t length, float gain);

#endif