#include <iostream>
#include <assert.h>
#include "Gameboard.h"

Gameboard::Gameboard() {
    // initializing empty grid
    empty();
}

void Gameboard::pointValid(Point pt) const {
    return pointValid(pt.getX(), pt.getY());
}

void Gameboard::pointValid(int x, int y) const {
    bool point_in_range = true;
    // if point outside of our ranges we return false
    if (( x > MAX_X ) || // x value to big
        (x < 0) ||  // x value to small
        ( y > MAX_Y ) || // y val to big
        ( y < 0)) {  // y value to small
        point_in_range = false;
    }
    assert(point_in_range);
}

void Gameboard::empty() {
    for (int x = 0; x < MAX_X; x++){
        for (int y = 0; y < MAX_Y; y++){
            grid[x][y] = -1;
        }
    }
}

int Gameboard::getContent(Point pt) const {
    return grid[pt.getX()][pt.getY()];
}

int Gameboard::getContent(int x, int y) const {
    pointValid(x, y);
    return grid[x][y];
}


void Gameboard::setContent(Point pt, int content) {
    grid[pt.getX()][pt.getY()] = content;
}

void Gameboard::setContent(int x, int y, int content) {
    grid[x][y] = content;
}

void Gameboard::setContent(std::vector<Point> locs, int content) {
    for (int i = 0; i < locs.size(); i++){
        setContent(locs[i], content);
    }
}


bool Gameboard::areLocsEmpty(std::vector<Point> locs) const {
    for (int i = 0; i < locs.size(); i++){

        // verifying point is valid
        if (( locs[i].getX() > MAX_X ) || // x value to big
            (locs[i].getX() < 0) ||  // x value to small
            ( locs[i].getY() > MAX_Y ) || // y val to big
            (locs[i].getY() < 0)) {  // y value to small

            // this point is out of bounds, skipping
            continue;
        }

        // point is valid
        if ( getContent(locs[i]) != -1 ) {

            // point is not empty
            return false;
        }
    }
    // if we are here, every point was valid AND empty
    return true;
}

Point Gameboard::getSpawnLoc() const {
    return spawnLoc;
}

void Gameboard::printToConsole() const{

    // defining characters
    char emptyChar = '.';
    char printChar;
    std::string line = "";

    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {

            if (getContent( x, y ) != -1 ) {
                // temporarily making all non empty blocks hashes
                printChar = 48 + getContent(x, y);
            } else {
                // default is empty
                printChar = emptyChar;
            }

            // printing whatever
            line += printChar;
        }
        // printing newline
		//std::cout << "EXAMPLE LINE" + line <<  std::endl;
        std::cout << "EXAMPLE LINE"  <<  std::endl;
        line = "";
    }
}

bool Gameboard::isRowCompleted(int rowIndex) const {
    for (int x = 0; x < MAX_X; x++) {
        if (getContent(x, rowIndex) == -1) {
            // returning false if a single block is empty
            return false;
        }
    }
    // we got here so every block must be full
    return true;

}

void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
    for (int x = 0; x < MAX_X; x++) {
        setContent(x, targetRowIndex, getContent(x, sourceRowIndex));
    }
}

void Gameboard::fillRow(int rowIndex, int content) {
    for (int x = 0; x < MAX_X; x++) {
        setContent(x, rowIndex, content);
    }
}


void Gameboard::removeRow(int rowIndex) {
    //   1) Starting at rowIndex, copy each row above the removed
    //     row "one-row-downwards" in the grid.
    //     (loop from y=rowIndex to 0, and copyRowIntoRow(y-1, y)).
    for (int y=rowIndex; y > 0; y--){
        copyRowIntoRow(y - 1, y);
    }

    //   2) call filGameboard::EMPTY_BLOCKow() on the first row (and place EMPTY_BLOCKs in it).
    fillRow(0, Gameboard::EMPTY_BLOCK);
}


void Gameboard::removeRows(std::vector<int> rowIndices) {
    for (int i = 0; i < rowIndices.size(); i++) {
        removeRow(rowIndices[i]);
    }
}

std::vector<int> Gameboard::getCompletedRowIndices() const {

    std::vector<int> completed;

    for (int y = 0; y < MAX_Y; y++){
        if (isRowCompleted(y)) {
            // if this row is completed, add it to the list of completed rows.
            completed.push_back(y);
        }
    }

    return completed;
}

int Gameboard::removeCompletedRows() {
    // getting completed rows
    std::vector<int> completed = getCompletedRowIndices();

    // removing the completed rows
    removeRows(completed);

    // what would we do without abstraction?
    return completed.size();
}


























