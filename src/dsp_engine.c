#include <stdio.h>
#include "dsp_engine.h"

void apply_low_pass(const int16_t* input, int16_t* output, uint32_t length){
    for(int i=2; i < length; i++){
        int32_t sum = 0;
        sum = ((input[i] + input[i - 1] + input[i - 2]) * 10922);
        output[i] = (int16_t)(sum >> 15);
    }
    output[0] = input[0];
    output[1] = input[1];
}

void apply_gain(int16_t* data, uint32_t length, float gain){
    for(int i=0; i < length; i++){
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