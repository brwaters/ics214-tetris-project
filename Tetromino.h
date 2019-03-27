//
// Created by Brendon Waters on 2019-03-04.
//

#ifndef FINALPROJECT_TETROMINO_H
#define FINALPROJECT_TETROMINO_H


#include <vector>
#include "Point.h"
#include <iostream>

enum TetColor { // all possible colors
	RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE
};

enum TetShape { // all possible shapes
	SHAPE_S, SHAPE_Z, SHAPE_L, SHAPE_J, SHAPE_O, SHAPE_I, SHAPE_T, TetShapeCount
};

class Tetromino {

private:
	TetColor color;
	TetShape shape;

protected:
	std::vector<Point> blockLocs;

public:
	friend class TestSuite;
	Tetromino();

	TetColor getColor() const; // returns the enumerated color
	TetShape getShape() const; // returns enumerated shape
	void setShape(TetShape shape); // sets shape
	void rotateCW();
		// rotate the shape 90 degrees around [0,0] (clockwise) // to do this:
		// - iterate through blockLocs
		// - rotate each Point 90 degrees around [0,0]
		// hint: rotate the point [1,2] clockwise around [0,0] and note // how the x,y values change. There are 2 functions in the Point
		// class that can be used to accomplish a rotation.
	void printToConsole() const;
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

	static TetShape getRandomShape();
};


#endif //FINALPROJECT_TETROMINO_H
