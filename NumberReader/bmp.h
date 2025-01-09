#pragma once

struct BitmapHeader {
	int headerSize;
	int width;
	int height;
	short colorPlaneNo;
	short bitePerPixel;
	int compressionMethod;
	int imgSize;
	int hResolution;
	int vResolution;
	int noOfColors;
	int importentColorsNo;
};

long decodeBMP(unsigned char* file, long size, void** bitStream);