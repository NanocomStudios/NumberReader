#include <iostream>

#include "process.h"
#include "bmp.h"
#include "files.h"

using namespace std;

int main() {
	std::cout << "Hello\n";
	double inp[] = { 1,2,3,4,5 };
	double weight[] = { 6,7,8,9,10,11,12,13,14,15 };
	double output[2];

	calculateOutputs(inp, 5, weight, output, 2);

	for (int i = 0; i < 2; i++) {
		cout << output[i] << " ";
	}cout << endl;

	long size = fileSize("3.bmp");

	if (size == -1) {
		cout << "error 1";
		exit(1);
	}

	FILE* fpt;
	fopen_s(&fpt, "3.bmp", "rb");

	if (fpt == NULL) {
		cout << "error 2";
		exit(2);
	}
	unsigned char* file = (unsigned char*)malloc(size);;

	cout << fread(file, 1, size, fpt) << endl;

	void* bitStream = NULL;

	long bitStreamSize = decodeBMP(file, size, &bitStream);

	for (long i = 0; i < bitStreamSize; i++) {
		cout << (int)*((char*)bitStream + i);
	}
}