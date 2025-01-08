#pragma once

#define IHDR *(int*)"IHDR"
#define IDAT *(int*)"IDAT"

struct HeadChunk {
	unsigned int width;
	unsigned int height;
	unsigned char bitDepth;
	unsigned char colorType;
	unsigned char compressionMethod;
	unsigned char filterMethod;
	unsigned char interlaceMethod;
};

long int fileSize(const char file_name[]);
long decodePNG(unsigned char* file, long size, void* bitStream);
char isValidPNG(unsigned char* file);
void toLittleEndian(void* inpArray, long size);
int readChunk(unsigned char* file, long* index, void** returnArry, long* returnSize);