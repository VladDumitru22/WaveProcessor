#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wav_header.h>

int main() {

    FILE *fptr = fopen("samples/Sample_Mono_02.wav", "rb");

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
    int totalSamples = header.subchunk2Size / (header.bitsPerSample / 8);
    if((header.bitsPerSample / 8) * totalSamples !=  header.subchunk2Size){
        printf("Invalid format.\n");
        return 1;
    }

    // Data for the audio without the metadata from the WAV file
    int16_t *audioData = (int16_t *)malloc(header.subchunk2Size);

    if(audioData == NULL){
        printf("Error: audioData is empty.\n");
        return 1;
    }

    fread(audioData, header.bitsPerSample / 8, totalSamples, fptr);
    
    printf("Chanels: %u\n", header.numChannels);
    for(int i=0; i<10; i++) {
        printf("Sample[%d]: %d\n", i, audioData[i]);
    }



    fclose(fptr);
    free(audioData);
    return 0;
}