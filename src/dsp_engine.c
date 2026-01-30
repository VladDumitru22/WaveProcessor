#include <stdio.h>
#include "dsp_engine.h"

void apply_low_pass(const int16_t* input, int16_t* output, uint32_t length, uint16_t channels){
    uint32_t edgeSamples = 2 * channels;
    for(uint32_t i = 0; i < edgeSamples && i < length; i++) {
        output[i] = input[i];
    }

    for(uint32_t i = edgeSamples; i < length; i++){
        int32_t sum = ((input[i] + input[i - channels] + input[i - 2 * channels]) * 10922);
        output[i] = (int16_t)(sum >> 15);
    }
}

void apply_high_pass(const int16_t* input, int16_t* output, uint32_t length, uint16_t channels){
    uint32_t edgeSamples = 2 * channels;
    for (uint32_t i = 0; i < edgeSamples && i < length; i++) {
        output[i] = 0;
    }

    for (uint32_t i = edgeSamples; i < length; i++) {
        int32_t low_pass_component = (input[i] + input[i - channels] + input[i - 2 * channels]) / 3;
        
        output[i] = input[i] - (int16_t)low_pass_component;
    }
}

void apply_gain(int16_t* data, uint32_t length, float gain){
    for(uint32_t i=0; i < length; i++){
        float temp = data[i] * gain;
        if(temp > 32767){ //Maximum number that can be storend in int16
            data[i] = 32767;
        }else if(temp < -32768){
            data[i] = -32768;
        }else{
            data[i] = (int16_t)temp;
        }
    }
}