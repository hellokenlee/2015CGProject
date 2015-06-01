#include "util.h"

// print vector
std::ostream & operator << (std::ostream &output, const array<double, 3> vect) {
	output << "(" << vect[0];
	output << ", " << vect[1];
	output << ", " << vect[2];
	output << ")";
	return output;
}

// calculate the norm for a vector
double norm(array<double, 3> vect) {
	return sqrt(vect[0] * vect[0] +
		vect[1] * vect[1] +
		vect[2] * vect[2]);
}

// standardize a vector
array<double, 3> standardize(array<double, 3> vect) {
	double n = norm(vect);
	array<double, 3> stdVect;
	if (n != 0.0) {
		stdVect[0] = vect[0] / n;
		stdVect[1] = vect[1] / n;
		stdVect[2] = vect[2] / n;
	} else {
		stdVect[0] = stdVect[1] = stdVect[2] = 0.0;
	}
	return stdVect;
}

// numerical multiplication for a vector
array<double, 3> operator * (double n, array<double, 3> vect) {
	array<double, 3> result;
	result[0] = n * vect[0];
	result[1] = n * vect[1];
	result[2] = n * vect[2];
	return result;
}

// addition of two vectors
array<double, 3> operator + (array<double, 3> x, array<double, 3> y) {
	array<double, 3> result;
	result[0] = x[0] + y[0];
	result[1] = x[1] + y[1];
	result[2] = x[2] + y[2];
	return result;
}

// subtraction of two vectors
array<double, 3> operator - (array<double, 3> x, array<double, 3> y) {
	array<double, 3> result;
	result[0] = x[0] - y[0];
	result[1] = x[1] - y[1];
	result[2] = x[2] - y[2];
	return result;
}

// calculate dot product
double dot(array<double, 3> x, array<double, 3> y) {
	return x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
}

// calculate cross product
array<double, 3> cross(array<double, 3> x, array<double, 3> y) {
	array<double, 3> n;
	n[0] = x[1] * y[2] - x[2] * y[1];
	n[1] = -(x[0] * y[2] - x[2] * y[0]);
	n[2] = x[0] * y[1] - x[1] * y[0];
	return n;
}
