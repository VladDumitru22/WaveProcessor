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
        // Clipping check
        if(temp > 32767){ //Maximum number that can be storend in int16
            data[i] = 32767;
        }else if(temp < -32768){
            data[i] = -32768;
        }else{
            data[i] = (int16_t)temp;
        }
    }
}

void apply_echo(const int16_t* input, int16_t* output, uint32_t length, uint32_t sampleRate, uint16_t channels, float delaySeconds, float decay) {
    uint32_t offset = (uint32_t)(delaySeconds * sampleRate) * channels;

    for (uint32_t i = 0; i < length; i++) {
        if (i < offset) {
            output[i] = input[i];
        } else {
            int32_t combined = input[i] + (int32_t)(input[i - offset] * decay);
            if (combined > 32767){ 
                output[i] = 32767;
            }else if (combined < -32768){
                output[i] = -32768;
            }else{
                output[i] = (int16_t)combined;
            }
        }
    }
}