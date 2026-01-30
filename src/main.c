#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wav_header.h>
#include <dsp_engine.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input.wav> <output.wav>\n", argv[0]);
        return 1;
    }

    FILE *fptr = fopen(argv[1], "rb");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    WAVHeader header;
    fread(&header, sizeof(WAVHeader), 1, fptr);
    if(strncmp(header.chunkID, "RIFF", 4) != 0){
        printf("Error: File is not an WAV file.\n");
        return 1;
    }

    printf("Sample rate: %u\n", header.sampleRate);
    printf("Bits per sample: %u\n", header.bitsPerSample);

    // Total samples
    uint32_t totalSamples = header.subchunk2Size / (header.bitsPerSample / 8);
    if((header.bitsPerSample / 8) * totalSamples !=  header.subchunk2Size){
        printf("Invalid format.\n");
        return 1;
    }

    // Data for the audio without the metadata from the WAV file
    int16_t *audioData = (int16_t *)malloc(header.subchunk2Size);
    if(audioData == NULL){
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    fread(audioData, header.bitsPerSample / 8, totalSamples, fptr);
    
    printf("Chanels: %u\n", header.numChannels);
    for(int i=0; i<10; i++) {
        printf("Sample[%d]: %d\n", i, audioData[i]);
    }

    //A second space in memory to store the filtered result.
    int16_t *outputData = (int16_t *)malloc(header.subchunk2Size);
    if(outputData == NULL){
        printf("Error: Memory allocation failed.\n");
        free(audioData);
        free(outputData);
        return 1;
    }

    int choice;
    float userGain = 1.0f;

    printf("\n--- WavProcessor Menu ---\n");
    printf("1. Low-Pass Filter\n");
    printf("2. High-Pass Filter\n");
    printf("3. Apply Echo\n");
    printf("4. No filter\n");
    printf("Select filter: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return 1; 
    }
    printf("Enter gain: ");
    if (scanf("%f", &userGain) != 1) {
        printf("Invalid gain! Please enter a decimal number.\n");
        return 1;
    }

    // Executăm alegerea
    switch(choice) {
        case 1:
            apply_low_pass(audioData, outputData, totalSamples, header.numChannels);
            break;
        case 2:
            apply_high_pass(audioData, outputData, totalSamples, header.numChannels);
            break;
        case 3: {
            float delaySeconds, decay;
            printf("Enter delay seconds: ");
            if (scanf("%f", &delaySeconds) != 1) {
                printf("Invalid gain! Please enter a decimal number.\n");
                return 1;
            }
            printf("Enter decay: ");
            if (scanf("%f", &decay) != 1) {
                printf("Invalid gain! Please enter a decimal number.\n");
                return 1;
            }
            apply_echo(audioData, outputData, totalSamples, header.sampleRate, header.numChannels, delaySeconds, decay);
            break;
        }
        default:
            memcpy(outputData, audioData, header.subchunk2Size);
            break;
    }

    // Aplicăm gain-ul la final pe rezultatul filtrat
    apply_gain(outputData, totalSamples, userGain);
    //FIR Filter logic

    FILE *fptrOut = fopen(argv[2], "wb");
    if(fptrOut == NULL){
        printf("Error: Could not open file.\n");
        free(audioData);
        free(outputData);
        return 1;
    }

    fwrite(&header, sizeof(WAVHeader), 1, fptrOut);
    fwrite(outputData, header.bitsPerSample / 8, totalSamples, fptrOut);

    fclose(fptr);
    fclose(fptrOut);
    free(audioData);
    free(outputData);

    return 0;
}