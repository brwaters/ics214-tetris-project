//
// Created by Brendon Waters on 2019-03-04.
//

#include "Tetromino.h"

#include <vector>
#include "Point.h"
#include <iostream>

using namespace std;

TetShape Tetromino::getRandomShape() {
	TetShape randomShape = TetShapeCount;
	int randShapeInt = rand() % static_cast<int>(randomShape);
	return static_cast<TetShape>(randShapeInt);
}

Tetromino::Tetromino() { // Could you rand % 6 to get a random color bases on enum values?
	this->color = RED;
	this->shape = getRandomShape();
}

TetColor Tetromino::getColor() const {
	return this->color;
}

TetShape Tetromino::getShape() const {
	return this->shape;
}

void Tetromino::setShape(TetShape shape) {
	// set the shape
	// - clear any blockLocs set previously
	//  - set the blockLocs for the shape
	//  - set the color for the shape
	this->shape = shape;
	blockLocs.clear();
	switch (shape) {
		case SHAPE_S : blockLocs = {Point(0, 0), Point(-1, 0), Point(0, 1), Point(1, 1)};
			this->color = RED;
			break;
		case SHAPE_Z : blockLocs = {Point(0,0), Point(0, 1), Point(-1, 1), Point(1, 0)};
			this-> color = ORANGE;
			break;
		case SHAPE_L : blockLocs = {Point(0,0), Point(0,1), Point(0,-1), Point(1, -1)};
			this->color = YELLOW;
			break;
		case SHAPE_J : blockLocs = {Point(0,0), Point(0,-1), Point(-1,-1), Point(0, 1)};
			this->color = GREEN;
			break;
		case SHAPE_O : blockLocs = {Point(0,0), Point(0,1), Point(1, 1), Point(1, 0)};
			this->color = BLUE_LIGHT;
			break;
		case SHAPE_I : blockLocs = {Point(0,0), Point(0, 1), Point(0, 2), Point(0, -1)};
			this->color = BLUE_DARK;
			break;
		case SHAPE_T : blockLocs = {Point(0,0), Point(-1, 0), Point(1, 0), Point(0, -1)};
			this->color = PURPLE;
			break;
	};
}
void Tetromino::rotateCW() {
	// rotate the shape 90 degrees around [0,0] (clockwise) // to do this:
	// - iterate through blockLocs
	// - rotate each Point 90 degrees around [0,0]
	// hint: rotate the point [1,2] clockwise around [0,0] and note // how the x,y values change. There are 2 functions in the Point
	// class that can be used to accomplish a rotation.
	for (int i = 0; i < blockLocs.size(); i++) {
		blockLocs[i].swapXY();
		blockLocs[i].multiplyY(-1);
	}

}
void Tetromino::printToConsole() const {
	// print a grid to display the current shape
	// to do this:
	// print out a “grid” of text to represent a co-ordinate
	// system. Start at top left [-3,3] go to bottom right [3,-3] // (use nested for loops)
	// for each [x,y] point, loop through the blockLocs and if
	// the point exists in the list, print an 'x' instead of a '.' // You should end up with something like this:
	// (results will vary depending on shape and rotation, eg: this // one shows a T shape rotated clockwise once)
	// .......
	// .......
	// ...x...
	// ..xx...
	// ...x...
	// .......
	cout << "Print to console called." << endl;
	for (int y = 3;  y >= -3; y--) {
		for (int x = -3; x <= 3; x++) {
			bool match = false;
			for (int k = 0; k < blockLocs.size(); k++) {
				if (blockLocs[k].getX() == x && blockLocs[k].getY() == y) {
					match = true;
				}
			}
			if (match) {
				cout << 'x';
			} else {
				cout << '.';
			}
		}
		cout << endl;
	}
}