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

class Point {
public:
    float x,y;
    Point(float x, float y):x(x),y(y){}


public float xVal() {
    return x;
}
public float yVal() {
    return y;
}
}
// we create an array of x's from points
public float[] from_point_to_x(**points, int size) {
float[] fromPointToFloat = new float[size];
for(i = 0; i < size; i++) {
    float[i] == points[i].xVal;
}
return fromPointToFloat;
}

// we create an array of y's from points
public float[] from_point_to_y(**points, int size) {
float[] fromPointToFloat = new float[size];
for(i = 0; i < size; i++) {
    float[i] == points[i].yVal;
}
return fromPointToFloat;
}

//we calculate here the avarages of the x and y of the points
public float avarage_calculator(float **vals, int size) {
    int sum;
    for(i = 0; i < size; i++) {
        sum += vals[i];
    }
    floatSize = (float)size;
    return (sum / floatSize);
}
// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size) {
float[] fromPointToX = new float[size];
float[] fromPointToY = new float[size];
float yAvarage;
float xAvarage;
float varA;
float varB;
fromPointToX = from_point_to_x(points, size);
fromPointToY = from_point_to_y(points, size);
xAvarage = avarage_calculator(fromPointToX, size);
yAvarage = avarage_calculator(fromPointToY, size);
varA = (cov(fromPointToX, fromPointToY, size)) / (var(fromPointToX));
varB = fromPointToY - (varA * fromPointToX);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);