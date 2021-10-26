#include <valarray>
#include "anomaly_detection_util.h"
#include "math.h"

float var(float *x, int size) {
    float var = 0;
    for (int i = 1; i <= size; ++i) {
        var = var + pow(x[i], 2));
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

// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);