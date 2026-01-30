#ifndef DSP_ENGINE_H
#define DSP_ENGINE_H

#include <stdint.h>

void apply_low_pass(const int16_t* input, int16_t* output, uint32_t length);

#endif