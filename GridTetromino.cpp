//
// Created by Brendon Waters on 2019-03-25.
//

#include "GridTetromino.h"


GridTetromino::GridTetromino() {
	// constructor, initialize gridLoc to 0,0
	this->gridLoc = Point(0,0);
}

Point GridTetromino::getGridLoc() const {
	// return the tetromino's grid/gameboard loc (x,y)
	return gridLoc;
}
void GridTetromino::setGridLoc(int x, int y) {
	// sets the tetromino's grid/gameboard loc using x,y
	gridLoc.setXY(x, y);
}
void GridTetromino::setGridLoc(const Point& pt) {
	// sets the tetromino's grid/gameboard loc using a Point
	this->gridLoc = pt;
}

// transpose the gridLoc of this shape
//	(1,0) represents a move to the right (x+1)
//	(-1,0) represents a move to the left (x-1)
//	(0,1) represents a move down (y+1)
void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc.setX(gridLoc.getX() + xOffset);
	gridLoc.setY(gridLoc.getY() + yOffset);
}

// build and return a vector of Points to represent our inherited
// blockLocs vector mapped to the gridLoc of this object instance.
// eg: if we have a Point [x,y] in our vector,
// and our gridLoc is [5,6] the mapped Point would be [5+x,6+y].
std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
	std::vector<Point> blockLocsOnGrid;
	for (auto pt : blockLocs) {
		pt.setX(pt.getX() + gridLoc.getX());
		pt.setY(pt.getY() + gridLoc.getY());
		blockLocsOnGrid.push_back(pt);
	}
	return blockLocsOnGrid;
}


// MEMBER VARIABLES
Point gridLoc;	// the [x,y] location of this tetromino on the grid/gameboard.
// This loc changes each time the tetromino moves.
