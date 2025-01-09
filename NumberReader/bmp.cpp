#include <iostream>

#include "bmp.h"

using namespace std;

long decodeBMP(unsigned char* file, long size, void** bitStream) {
	long bitStreamSize;
	if (*(short*)file == *(short*)"BM") {

		BitmapHeader* bitmapHeader = (BitmapHeader*)(file + 14);

		if (bitmapHeader == NULL) {
			return -2;
		}

		cout << "Height : " << bitmapHeader->height << endl
			<< "Width : " << bitmapHeader->width << endl;

		if (bitmapHeader->height != bitmapHeader->width) {
			return -3;
		}

		bitStreamSize = bitmapHeader->height * bitmapHeader->width;

		cout << bitStreamSize << endl;

		*bitStream = malloc(bitStreamSize);

		if (*bitStream == NULL) {
			return -4;
		}

		for (long i = 0; i < bitmapHeader->height; i++) {
			for (long j = 0; j < bitmapHeader->width; j++) {
				*(*(unsigned char**)bitStream + (i * bitmapHeader->width) + j) = *(file + size - 1 - ((i + 1) * bitmapHeader->width) + j);

				if ((int)*(*(unsigned char**)bitStream + (i * bitmapHeader->width) + j)) {
					*(*(unsigned char**)bitStream + (i * bitmapHeader->width) + j) = 1;
					cout << "X";
				}
				else {
					*(*(unsigned char**)bitStream + (i * bitmapHeader->width) + j) = 0;
					cout << ".";
				}

			}
			cout << endl;
			
		}

	}
	else {
		return -1;
	}
	return bitStreamSize;
}

