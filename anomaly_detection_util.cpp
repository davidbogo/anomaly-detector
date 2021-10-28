#include <valarray>
#include "anomaly_detection_util.h"
#include "math.h"

float var(float *x, int size) {
    float var = 0;
    for (int i = 1; i <= size; ++i) {
        var = var + pow(x[i], 2);
    }
    var = var / float(size);
    var = var - pow(expectedValue(x, size), 2);
    return var;
}

float expectedValue(float *x, int size) {
    float sum = 0;
    for (int i = 1; i <= size; ++i) {
        sum = sum + x[i];
    }
    return sum / (float) size;
}

float cov(float *x, float *y, int size) {
    float y_expectedValue = expectedValue(y, size);
    float x_expectedValue = expectedValue(x, size);
    float sum = 0;
    for (int i = 1; i <= size; i++) {
        sum += (x[i] - x_expectedValue) * (y[i] - y_expectedValue);
    }
    float cov_x_y = sum / float(size);
    return cov_x_y;
}

float pearson(float *x, float *y, int size) {
    float numerator = cov(x, y, size);
    float denominator = sqrt(var(x,size)) * sqrt(var(y,size));
    return numerator/denominator;

}

// we create an array of x's from points
static float *from_point_to_x(Point **points, int size)
{
	float *fromPointToFloat = new float[size];
	for (int i = 0; i < size; i++) {
		fromPointToFloat[i] = points[i]->x;
	}
	return fromPointToFloat;
}

// we create an array of y's from points
static float *from_point_to_y(Point **points, int size)
{
	float *fromPointToFloat = new float[size];
	for (int i = 0; i < size; i++) {
		fromPointToFloat[i] = points[i]->y;
	}
	return fromPointToFloat;
}

//we calculate here the avarages of the x and y of the points
static float avarage_calculator(float *vals, int size)
{
    float sum;
    for (int i = 0; i < size; i++) {
        sum += vals[i];
    }
    return (sum / (float)size);
}

// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size)
{
	float *fromPointToX = from_point_to_x(points, size);
	float *fromPointToY = from_point_to_y(points, size);
	float xAvarage = avarage_calculator(fromPointToX, size);
	float yAvarage = avarage_calculator(fromPointToY, size);
	float varA = (cov(fromPointToX, fromPointToY, size)) / (var(fromPointToX, size));
	float varB = (yAvarage) - (varA * xAvarage);
	delete[] fromPointToY;
	delete[] fromPointToX;
	Line lineReg(varA, varB);
	return lineReg;
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);