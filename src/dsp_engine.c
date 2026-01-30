#include <stdio.h>
#include "dsp_engine.h"

void apply_low_pass(const int16_t* input, int16_t* output, uint32_t length){
    for(int i=2; i < length; i++){
        int32_t sum = 0;
        sum = ((*(input + i) + *(input + (i - 1)) + *(input + (i - 2))) * 10922);
        *(output + i) = (int16_t)(sum >> 15);
    }
    output[0] = input[0];
    output[1] = input[1];
}