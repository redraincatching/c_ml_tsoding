#include <stdio.h>
#include <stdlib.h>

// training data, predicts the output number based on the input
float train[][2] = {
	{0,0},
	{1,2},
	{2,4},
	{3,6},
	{4,8}
};
#define train_count (sizeof(train)/sizeof(train[0]))

// all we know about the data is that it follows the form
// y = x*w;

// generate a random float [0,1]
float rand_float(void) {
	// rand() generates a number between 0 and RAND_MAX
	return (float) rand() / (float) RAND_MAX;
}

// cost function to measure our model
// args: weight, bias
float cost(float w, float b) {
	float result = 0.0f;

	for (size_t i = 0; i < train_count; ++i) {
		float x = train[i][0];
		// so we take that input and feed it into our model
		float y = x * w + b;
		// then check against the expected result
		// we also need a measure of how close our model is
	
		// so we get the difference between expected and output
		float d = y - train[i][1];
		// then accumulate their squares
		result += d*d;	// two reasons, it ensures nonzero, and amplifies errors
	}

	result /= train_count;
	return result;
}

int main() {
	// seed rand	
	// srand(time(0));
	// for testing purposes
	srand(420);
	float w = rand_float() * 10.0f;
	float b = rand_float() * 5.0f;

	// so we need to modify our parameter to make it fit better
	// so epsilon here is a small change
		// and we can use this to approximate derivatives
	float eps = 1e-3;
	float rate = 1e-3;
	float reps = 10000;

	for (size_t i = 0; i < reps; ++i) {
		// and now we essentially find the derivative of the cost function from first principles
			// this is a little stupid but it's fine
			// it's called finite difference
			// we want to find the local minimum of the function
		float c = cost(w, b);
		float d_cost = (cost(w + eps, b) - c) / eps;
		float d_bias = (cost(w, b + eps) - c) / eps;

		// but the derivative is actually too big, so we'll multiply that by the learning rate
		w -= rate * d_cost;
		b -= rate * d_bias;

		printf("cost = %f, w = %f, b = %f\n", c, w, b);
	}

	// and see what our number is after however many repetitions, should be ~= 2
	printf("------------------\n");
	printf("w = %f, b = %f\n", w, b);
	
	return 0;
}
