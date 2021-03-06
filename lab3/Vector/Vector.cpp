#include "stdafx.h"
#include "Vector.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <windows.h>

#define PI 3.14159265

Vector::Vector() {
	this->x = 0;
	this->y = 0;
}

Vector::Vector(double x, double y) {
	this->x = x;
	this->y = y;
}

double Vector::angle() {
	return atan2(y, x) * 180 / PI;
}

double Vector::length() {
	return sqrt(x * x + y * y);
}

void Vector::print() {
	std::cout << std::setprecision(4) << "Vector (" << x << ", " << y << ")" << std::endl;
}

Vector* createVector(double x, double y) {
	return new Vector(x, y);
}