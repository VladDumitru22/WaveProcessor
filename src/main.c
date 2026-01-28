#include <stdio.h>
#include <string.h>
#include <wav_header.h>

int main() {

    FILE *fptr = fopen("samples/Sample_01.wav", "rb");

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

    fclose(fptr);


    return 0;
}