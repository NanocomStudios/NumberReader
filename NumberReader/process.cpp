#include "process.h"

void calculateOutputs(double* input, int input_size, double* weights, double* output, int output_size) {
	for (int i = 0; i < output_size; i++) {
		for (int j = 0; j < input_size; j++) {
			output[i] += input[j] * weights[j + (i * input_size)];
		}
	}
}