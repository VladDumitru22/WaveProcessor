#include <stdint.h>

#pragma pack(push, 1) //Remove padding in memory

typedef struct WAVHeader {
    // RIFF Chunk Descriptor
    char chunkID[5];
    uint32_t chunkSize;
    char format[5];

    // Fmt Sub-chunk
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;  
    uint16_t bitsPerSample;  

    // Data Sub-chunk
    char subchunk2ID[4];
    uint32_t subchunk2Size;   

} WAVHeader;

#pragma pack(pop) //Get back to default padding