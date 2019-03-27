#include "GridTetromino.h"
#include "Point.h"
#include <iostream>
#include <string>

GridTetromino::GridTetromino() {
	gridLoc = Point(0, 0);
}

Point GridTetromino::getGridLoc() const {
	return gridLoc;
}
void GridTetromino::setGridLoc(int x, int y) {
	gridLoc = Point(x, y);
}
void GridTetromino::setGridLoc(const Point& pt) {
	gridLoc = pt;
}

void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc.setXY(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {

	std::vector<Point> newLocs;
	std::vector<Point> blockLocs = getBlockLocs();

	for (int i = 0; i < blockLocs.size(); i++) {
		Point newPt = Point(blockLocs[i].getX() + gridLoc.getX(), blockLocs[i].getY() + gridLoc.getY());
		newLocs.push_back(newPt);
	}

	return newLocs;

}

