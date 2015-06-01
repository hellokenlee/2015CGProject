#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#define PATH_SIZE 250
#define show(a) std::cout<<a<<std::endl
#define max(a,b) return a>b?a:b; 
#define min(a,b) return a<b?a:b;
using namespace std;

#include <array>
#include <math.h>
std::ostream & operator << (std::ostream &output, const array<double, 3> vect);
double norm(array<double, 3> vect);
array<double, 3> standardize(array<double, 3> vect);
array<double, 3> operator * (double n, array<double, 3> vect);
array<double, 3> operator + (array<double, 3> x, array<double, 3> y);
array<double, 3> operator - (array<double, 3> x, array<double, 3> y);
double dot(array<double, 3> x, array<double, 3> y);
array<double, 3> cross(array<double, 3> x, array<double, 3> y);

#endif
