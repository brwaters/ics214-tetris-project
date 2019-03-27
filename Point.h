//
// Created by Brendon Waters on 2019-03-04.
//

#ifndef FINALPROJECT_POINT_H
#define FINALPROJECT_POINT_H

#include <string>

class Point {

private:
	int x;
	int y;

public:
	friend class TestSuite;
	Point(); // constructor with no params

	Point(int newX, int newY); // constuctor with params

	int getX() const; // return x attribute of Point obj

	int getY() const; // return y attr of Point obj

	void setX(int x); // set x attr

	void setY(int y); // set y attr

	void setXY(int x, int y); // set both x and y at the same time

	void swapXY(); // swap x with y and vice-versa

	void multiplyX(int x); // multiply x by a factor supplied

	void multiplyY(int y); // multiply y by a factor supplied

	std::string toString() const;

};


#endif //FINALPROJECT_POINT_H
