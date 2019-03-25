#include "Tetromino.h"
#include <iostream>
#include <string>

// returns color of Tetromino
TetColor Tetromino::getColor() {
	return color;
}

// returns the shape of Tetromino
TetShape Tetromino::getShape() {
	return shape;
}

void Tetromino::setShape(TetShape shape) {
	// set the shape     
	this->shape = shape;

	//  - set the color for the shape 
	this->color = static_cast<TetColor>(shape);

	//  - clear any blockLocs set previously     
	blockLocs.empty();

	//  - set the blockLocs for the shape     
	switch (shape){
		case TetShape::SHAPE_S:
			blockLocs = {
				Point(-1, 0),
				Point(0, 0),
				Point(0, 1),
				Point(1, 1)
			};
			break;
		case TetShape::SHAPE_O:
			blockLocs = {
				Point(0, 1),
				Point(1, 1),
				Point(0, 0),
				Point(1, 0)
			};
			break;
		case TetShape::SHAPE_I:
			blockLocs = {
				Point(0, 0),
				Point(0, -1),
				Point(0, 1),
				Point(0, 2),
			};
			break;
		case TetShape::SHAPE_Z:
			blockLocs = {
				Point(0, 0),
				Point(0, 1),
				Point(1, 0),
				Point(-1, 1),
			};
			break;
		case TetShape::SHAPE_L:
			blockLocs = {
				Point(0, 1),
				Point(0, 0),
				Point(0, -1),
				Point(1, -1),
			};
			break;
		case TetShape::SHAPE_J:
			blockLocs = {
				Point(0, 1),
				Point(0, 0),
				Point(0, -1),
				Point(-1, -1),
			};
			break;
		case TetShape::SHAPE_T:
			blockLocs = {
				Point(0, 0),
				Point(1, 0),
				Point(-1, 0),
				Point(0, -1),
			};
			break;
	}
}

void Tetromino::rotateCW() {
	//  - iterate through blockLocs     
	for (int i = 0; i < blockLocs.size(); i++) {
		//  - rotate each Point 90 degrees around [0,0]     
		blockLocs[i].swapXY();
		
		// we need to negate what ever value Y has
		blockLocs[i].multiplyY(-1);
	}

}
// rotate the shape 90 degrees around [0,0] (clockwise)     
// to do this:     
// hint: rotate the point [1,2] clockwise around [0,0] and note     
// how the x,y values change. There are 2 functions in the Point     
// class that can be used to accomplish a rotation.   

void Tetromino::printToConsole() const{

	// this variable is for checking if the point we are 
	// looking at is a point on the tetromino
	bool tetPoint = false;

	// looping through grid
	for (int y = 10; y >= -10; y--) {
		for (int x = -10; x < 10; x++) {
			// for each point

			// reseting tetPoint
			tetPoint = false;
					
			// checking if its a point on the tetromino
			// normally I would want to have the condition be i < something.length.
			// but I dont know if vectors support that and I do know that it will always have 
			// a length of 4
			for (int i = 0; i < 4; i++) {
				if (blockLocs[i].getX() == x && blockLocs[i].getY() == y) {
					// This point is on the tetromino, printing alternative character
					std::cout << 'X';
					tetPoint = true;
					break;
				}
			}

			// if this is just another point on our matrix, we just print '.'
			if (!tetPoint) {
				std::cout << '.';
			}
		}
		// adding new line
		std::cout << std::endl;
	}
}
// print a grid to display the current shape     
// to do this:     
// print out a “grid” of text to represent a co-ordinate     
// system.  Start at top left [-3,3] go to bottom right [3,-3]     
// (use nested for loops)     
//  for each [x,y] point, loop through the blockLocs and if     
//  the point exists in the list, print an 'x' instead of a '.'     
// You should end up with something like this:     
// (results will vary depending on shape and rotation, eg: this     
//  one shows a T shape rotated clockwise once)     
//  .......     
//  .......     
//  ...x...     
//  ..xx...     
//  ...x...     
//  .......