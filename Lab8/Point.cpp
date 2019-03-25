#include "Point.h"
#include <iostream>
#include <string>

// returns x value of point
int Point::getX() const {
	return x;
}

// returns y value of point
int Point::getY() const {
	return y;
}

// sets x
void Point::setX(int newX) {
	x = newX;
}

// sets y
void Point::setY(int newY) {
	y = newY;
}

// sets, get this, both x and y
void Point::setXY(int newX, int newY) {
	x = newX;
	y = newY;
}

// swaps x and y values for some reason
void Point::swapXY() {
	int tmp = x;
	x = y;
	y = tmp;
}

// multiplies x by a certain amount
void Point::multiplyX(int factor) {
	x *= factor;
}

// multiplies y by a certain amount
void Point::multiplyY(int factor) {
	y *= factor;
}

// return a string in the form [x,y] to represent the state
// of a point for debugging
std::string Point::toString() const {
	// converting x and y to string
	std::string xStr = std::to_string(x);
	std::string yStr = std::to_string(y);
	return "[" + xStr + "," + yStr + "]";
}