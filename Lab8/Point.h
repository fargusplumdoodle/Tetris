#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#include <iostream>

class Point {
public:
	// empty constructor, probably dont ever use
	Point() {
		x = 0;
		y = 0;
	}

	// use this one instead
	Point(int newX, int newY) {
		x = newX;
		y = newY;
	}

	// returns x value of point
	int getX() const;

	// returns y value of point
	int getY() const;

	// sets x
	void setX(int newX);

	// sets y
	void setY(int newY);

	// sets, get this, both x and y
	void setXY(int newX, int newY);

	// swaps x and y  for clockwise rotation
	void swapXY();

	// multiplies x by a certain amount
	void multiplyX(int factor);

	// multiplies y by a certain amount
	void multiplyY(int factor);

	// return a string in the form [x,y] to represent the state
	// of a point for debugging
	std::string toString() const;

private:
	// declaring X and Y values for point
	int x;
	int y;
};
#endif /* POINT_H */
