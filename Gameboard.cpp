//
// Created by Brendon Waters on 2019-03-18.
//
// The Gameboard class encapsulates the functionality of the Tetris game board.
// It is essentially a grid of blocks, and we will implement it with a 2D array.
//
// The Gameboard class has no concept of what a tetromino is!
// This is intentional abstraction and makes the gameboard's implementation as
// simple as possible. The gameboard class simply manages a 2D array of content
// (integers). Each integer of content can represent either an empty spot, or a
// color.  Gameboard member functions operate on that content (particularly on
// rows) to facilitate operations that happen on a Tetris gameboard (checking for
// a complete row, filling a row, copying a row, collapsing rows, etcÖ).
//
// Actual gameplay is handled by a separate class (which makes use of the gameboard).
// We will handle this in a future lab. To get a sense of the bigger picture and how
// the gameboard is used : a GridTetromino (a special Tetromino that has knowledge of
// its location on a co-ordinate system) will eventually reach a location on the
// gameboard where it cannot move down any further (because the points that it would
// occupy already contain content).At this point, the information that a Tetromino
// contains about its blocks (location and color) will be copied to the gameboard grid.
// We use the gameboard to determine what points are already occupied as a result of
// previous tetrominoes being ìlockedî, and what the contents are.It deals strictly in
// terms of[x][y] locations, and content(color, or EMPTY_BLOCK)
//
// Displaying the board(via text output) should show empty spots, and areas where blocks
// of color(content) have been copied("locked") onto the board from tetrominos that have
// already been placed(either intentionally or not).
//
// - The game board is represented by a 2D array of integers(the grid).
// - The array contains content(integers) which represent either :
//    - an EMPTY_BLOCK(-1),
//    - a color from the Tetromino::TetColor enum.
// - This 2D array is oriented with[0][0] at the top left and[MAX_X][MAX_Y] at the bottom
//     right. Why ? It makes it easier to draw the grid on the screen later because this
//     is the same way things are drawn on a screen co-ordinate system(where pixel 0, 0 is
//     considered top left).
// - Note that a 2D array normally has a[row][col] orientation.Since this grid is used as
//     a co-ordinate system, an[x][y] orientation is used where x (representing of the column
//     index) comes first, and y (representing the row index) comes second. This is the
//     opposite of what you'd normally expect of a 2D array.  If you were to print out the 2D
//     array using a [row][column] orientation, you would find that it is horizontal instead
//     of vertical and you may even exceed the bounds of the arrays!  If you simply think in
//     terms of an x, y co-ordinate system, you should be fine. Use 2 for loops to initialize
//     the array. Using an initializer list would be very confusing (because of the
//     orientation change).
//
//  [expected .cpp size: ~ 150 lines]

#include "Gameboard.h"
#include <vector>
#include "Point.h"
#include <iostream>
#include <iomanip>

using namespace std;


	// CONSTANTS
	static const int MAX_X = 10;		// gameboard x dimension
	static const int MAX_Y = 19;		// gameboard y dimension
	static const int EMPTY_BLOCK = -1;	// contents of an empty block

	// MEMBER FUNCTIONS

	Gameboard::Gameboard() { // constructor - empty() the grid
		empty();
	}

	int Gameboard::getContent(Point pt) const { // return the content at a given point
		return grid[pt.getX()][pt.getY()];
	}
	int Gameboard::getContent(int x, int y) const { // return the content at an x,y grid loc
		return grid[x][y];
	}

	void Gameboard::setContent(Point pt, int content) { // set the content at a given point
		grid[pt.getX()][pt.getY()] = content;
	}
	void Gameboard::setContent(int x, int y, int content) {    // set the content at an x,y grid loc
		grid[x][y] = content;
	}
	void Gameboard::setContent(std::vector<Point> locs, int content) {    // set the content for an array of grid locs
		for (auto &point : locs) {
			setContent(point, content);
		}
	}

	bool Gameboard::areLocsEmpty(std::vector<Point> locs) const {
		// return true if the content at all the locs specified is empty
		//   IMPORTANT NOTE: invalid x,y values can be passed to this method.
		//   Invalid meaning: outside the bounds of the grid.
		//   * Only test valid points (disregard the others - and ensure you
		//   don't use them to index into the grid).  Testing invalid points
		//   would likely result in an out of bounds error or segmentation fault!
		bool isEmpty = true;
		for (auto &point : locs) {
			if (point.getX() < MAX_X && point.getX() >= 0 && point.getY() < MAX_Y && point.getY() >= 0) {
				if (getContent(point) != EMPTY_BLOCK) {
					isEmpty = false;
				}
			}
		}
		return isEmpty;
	}
	int Gameboard::removeCompletedRows() {
		// removes all completed rows from the board
		//   use getCompletedRowIndices() and removeRows()
		//   return the # of completed rows removed
		std::vector<int> completeIndices = getCompletedRowIndices();
		removeRows(completeIndices);
		return completeIndices.size();
	}
	void Gameboard::empty() {
		// fill the board with EMPTY_BLOCK
		//   (iterate through each rowIndex and fillRow() with EMPTY_BLOCK))
		for (int y = 0; y < MAX_Y; y++) {
			fillRow(y, EMPTY_BLOCK);
		}

	}
	Point Gameboard::getSpawnLoc() const { // getter for the spawnLoc for new blocks
		return spawnLoc;
	}
	void Gameboard::printToConsole() const {
		// print the grid contents to the console (for debugging purposes)
		//   use setw(2) to space the contents out.
		for (int y = 0; y < MAX_Y; y++) {
			for (int x = 0; x < MAX_X; x++) {
				cout << setw(2) << grid[x][y];
			}
			cout << endl;
		}
	}

	 // These are private methods, so will need to be declared in the class

	bool Gameboard::isRowCompleted(int rowIndex) const {    // return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
		bool isFull = true;
			for (int x = 0; x < MAX_X; x++) {
				if (grid[x][rowIndex] == EMPTY_BLOCK) {
					isFull = false;
				}
		}
		return isFull;
	}

	std::vector<int> Gameboard::getCompletedRowIndices() const {
		// scan the board for completed rows.
		//   Iterate through grid rows and use isRowCompleted(rowIndex)
		//   return a vector of completed row indices.
		std::vector<int> completeIndices;
		for (int y = 0; y < MAX_Y; y++) {
			if (isRowCompleted(y)) {
				completeIndices.push_back(y);
			}
		}
		return completeIndices;
	}

	void Gameboard::removeRow(int rowIndex) {
		// In gameplay, when a full row is completed (filled with content)
		// it gets "removed".  To be exact, the row itself is not removed
		// but the content from the row above it is copied into it.
		// This continues all the way up the grid until the first row
		// is copied into the second row.  Finally, the first row is
		// filled with EMPTY_BLOCK
		// given a row index:
		//   1) Starting at rowIndex, copy each row above the removed
		//     row "one-row-downwards" in the grid.
		//     (loop from y=rowIndex to 0, and copyRowIntoRow(y-1, y)).
		//   2) call fillRow() on the first row (and place EMPTY_BLOCKs in it).
		for (rowIndex; rowIndex > 0; rowIndex--) {
			copyRowIntoRow(rowIndex - 1, rowIndex);
		}
		fillRow(0, EMPTY_BLOCK);

	}
	void Gameboard::removeRows(std::vector<int> rowIndices) {
		// given a vector of row indices, remove them
		//   (iterate through the vector and and call removeRow()
		//   on each row index).
		for (auto &row : rowIndices) {
			removeRow(row);
		}
	}

	void Gameboard::fillRow(int rowIndex, int content) {    // fill a given grid row with specified content
		for(int x = 0; x < MAX_X; x++) {
			grid[x][rowIndex] = content;
		}
	}

	void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
		// copy a source row's contents into a target row.
		for(int x = 0; x < MAX_X; x++) {
			grid[x][targetRowIndex] = grid[x][sourceRowIndex];
		}
	}
