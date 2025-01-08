#include <iostream>

#include "png.h"

using namespace std;

long decodePNG(unsigned char* file, long size, void* bitStream) {
    //printf("%X %X %X %X %X %X %X %X\n", file[0], file[1], file[2], file[3], file[4], file[5], file[6], file[7]);
    HeadChunk* headChunk = NULL;
    long index = 8;
    long chunkSize = 0;

    if (isValidPNG(file)) {
        cout << "Valid PNG file" << endl;

        if (readChunk(file, &index, (void**)&headChunk, &chunkSize) != IHDR) {
            return -1;
        }

        toLittleEndian(&(headChunk->width), sizeof(int));
        toLittleEndian(&(headChunk->height), sizeof(int));

        cout << "Width\t\t:\t" << headChunk->width << endl
            << "Height\t\t:\t" << headChunk->height << endl
            << "Bit Depth\t:\t" << (unsigned int)headChunk->bitDepth << endl
            << "Color Type\t:\t" << (unsigned int)headChunk->colorType << endl
            << "Compression\t:\t" << (unsigned int)headChunk->compressionMethod << endl
            << "Filter M\t:\t" << (unsigned int)headChunk->filterMethod << endl
            << "Interlace M\t:\t" << (unsigned int)headChunk->interlaceMethod << endl;

        free(headChunk);

        while (readChunk(file, &index, (void**)&headChunk, &chunkSize) != IDAT) {
            free(headChunk);
        }
        for (long i = 0; i < chunkSize; i++) {
            printf("%X ", *((unsigned char*)headChunk + i));
        }

    }
    return 0;
}

char isValidPNG(unsigned char* file) {
    if ((file[0] == 0x89) &&
        (file[1] == 0x50) &&
        (file[2] == 0x4e) &&
        (file[3] == 0x47) &&
        (file[4] == 0x0d) &&
        (file[5] == 0x0a) &&
        (file[6] == 0x1a) &&
        (file[7] == 0x0a)
        ) {
        return 1;
    }
    else return 0;
}

void toLittleEndian(void* inpArray, long size) {
    long i = 0;
    char tmp;
    size--;
    char* array = (char*)inpArray;
    printf("%X %X %X %X\n", (unsigned char)array[0], (unsigned char)array[1], (unsigned char)array[2], (unsigned char)array[3]);
    while (i < size) {
        tmp = array[size];
        array[size] = array[i];
        array[i] = tmp;
        i++;
        size--;
    }
    printf("%X %X %X %X\n", (unsigned char)array[0], (unsigned char)array[1], (unsigned char)array[2], (unsigned char)array[3]);
}

int readChunk(unsigned char* file, long* index, void** returnArray, long* returnSize) {

    int chunkSize = *(int*)(file + *index);
    toLittleEndian(&chunkSize, sizeof(int));

    *index += sizeof(int);
    cout << *index << endl;
    int chunkType = *(int*)(file + *index);

    *index += sizeof(int);
    cout << *index << endl;

    *returnArray = malloc(chunkSize);

    if (*returnArray == NULL) {
        return -1;
    }

    *returnSize = chunkSize;
    cout << *returnArray << endl;
    for (long i = 0; i < chunkSize; i++) {
        *(*(unsigned char**)returnArray + i) = *(file + *index + i);
    }

    *index += chunkSize + 4; // Skip CRC

    return chunkType;
}