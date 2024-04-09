#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef float training_data[3];

// sigmoid is one of the functions that can clamp the values given 0 < x < 1
float sigmoidf(float x) {
	return 1.f / (1.f + expf(-x));
}

// AND-gate
training_data and_train[] = {
	{0,0,0},
	{1,0,0},
	{0,1,0},
	{1,1,1}
};

// OR-gate
training_data or_train[] = {
	{0,0,0},
	{1,0,1},
	{0,1,1},
	{1,1,1}
};

// NAND-gate
training_data nand_train[] = {
	{0,0,1},
	{1,0,1},
	{0,1,1},
	{1,1,0}
};

training_data *train = or_train;
size_t train_count 4

// generate a random float [0,1]
float rand_float(void) {
	return (float) rand() / (float) RAND_MAX;
}

float cost(float w1, float w2, float b) {
	float result = 0.0f;
	for (size_t i = 0; i < train_count; ++i) {
		float x1 = train[i][0];
		float x2 = train[i][1];

		float y = sigmoidf(x1*w1 + x2*w2 + b);

		float d = y - train[i][2];
		result += d*d;
	}
	result /= train_count;
	return result;
}

int main(void) {
	srand(time(0));
	float w1 = rand_float();
	float w2 = rand_float();
	float b = rand_float();

	size_t reps = 100000;
	float eps = 1e-1;
	float rate = 1e-1;

	for (size_t i = 0; i < reps; ++i) {
		float c = cost(w1, w2, b);
		float dw1 = (cost(w1 + eps, w2, b) - c) / eps;
		float dw2 = (cost(w1, w2 + eps, b) - c) / eps;
		float db = (cost(w1, w2, b + eps) - c) / eps;

		w1 -= rate*dw1;
		w2 -= rate*dw2;
		b -= rate*db;

		// printf("cost = %f, w1 = %f, w2 = %f, b = %f\n", c, w1, w2, b);
	}

	printf("cost = %f, w1 = %f, w2 = %f, b = %f\n", cost(w1, w2, b), w1, w2, b);

	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			printf("%zu | %zu = %f\n", i, j, sigmoidf(i*w1 + j*w2 + b));
		}
	}

	return 0;
}
