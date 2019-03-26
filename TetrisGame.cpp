//
// Created by Brendon Waters on 2019-03-25.
//

#include "TetrisGame.h"

static const int BLOCK_WIDTH = 32;			// pixel width of a tetris block
static const int BLOCK_HEIGHT = 32;			// pixel height of a tetris block

// MEMBER FUNCTIONS

// constructor
//   assign pointers,
//   load font from file: fonts/RedOctober.ttf
//   setup scoreText
//   reset the game
TetrisGame::TetrisGame(sf::RenderWindow *window, sf::Sprite *blockSprite, Point gameboardOffset, Point nextShapeOffset) {
	pWindow = window;
	pBlockSprite = blockSprite;
	this->gameboardOffset = gameboardOffset;
	this->nextShapeOffset = nextShapeOffset;
	currentShape.setShape(Tetromino::getRandomShape());
}


// destructor, set pointers to null
TetrisGame::~TetrisGame() {

}

// draw anything to do with the game,
// includes board, currentShape, nextShape, score
void TetrisGame::draw() {
//	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
void TetrisGame::onKeyPressed(sf::Event event) {

}

// called every game loop to handle ticks & tetromino placement (locking)
void TetrisGame::processGameLoop(float secondsSinceLastLoop) {

}

// A tick() forces the currentShape to move (if there were no tick,
// the currentShape would float in position forever). This should
// call attemptMove() on the currentShape.  If not successful, lock()
// the currentShape (it can move no further), and record the fact that a
// shape was placed (using shapePlacedSinceLastGameLoop)
void TetrisGame::tick() {

}

// reset everything for a new game (use existing functions)
//  - setScore to 0
//  - determineSecondsPerTick(),
//  - clear the gameboard,
//  - pick & spawn next shape
//  - pick next shape again
void TetrisGame::reset() {

}

// assign nextShape.setShape a new random shape
void TetrisGame::pickNextShape() {

}


// copy the nextShape into the currentShape and set
//   its loc to be the gameboard's spawn loc.
//	 - return true/false based on isPositionLegal()
bool TetrisGame::spawnNextShape() {
	return true;
}



// test if a rotation is legal on the tetromino,
//   if so, rotate it.
//  To do this:
//	 1) create a (local) temporary copy of the tetromino
//	 2) rotate it (shape.rotateCW())
//	 3) test if temp rotatio was legal (isPositionLegal()),
//      if so - rotate the original tetromino.
//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptRotate(GridTetromino &shape) {
	return true;
}


// test if a move is legal on the tetromino, if so, move it.
//  To do this:
//	 1) create a (local) temporary copy of the current shape
//	 2) move it (temp.move())
//	 3) test if temp move was legal (isPositionLegal(),
//      if so - move the original.
//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptMove(GridTetromino &shape, int x, int y) {
	return true;
}


// drops the tetromino vertically as far as it can
//   legally go.  Use attemptMove(). This can be done in 1 line.
void TetrisGame::drop(GridTetromino &shape) {

}

// copy the contents of the tetromino's mapped block locs to the grid.
//	 1) get current blockshape locs via tetromino.getBlockLocsMappedToGrid()
//	 2) iterate on the mapped block locs and copy the contents (color)
//      of each to the grid (via gameboard.setGridContent())
void TetrisGame::lock(const GridTetromino &shape) {

}

// Graphics methods ==============================================

// draw a tetris block sprite on the canvas
// x,y are meant to be block offsets (not pixels), which means you
// will need to multiply them by BLOCK_WIDTH & BLOCK_HEIGHT
//  for help: www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
//	 1) set the block color using pBlockSprite->setTextureRect()
//   2) set the block loc using pBlockSprite->setPosition()
//	 3) draw the block using Window.draw()
// (pointers to window and sprite were passed into the constructor)
void TetrisGame::drawBlock(int x, int y, TetColor color, Point origin) {
	auto intColor = static_cast<int>(color);
	pBlockSprite->setTextureRect(sf::IntRect(intColor * 32, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
	pBlockSprite->setPosition(origin.getX() + x * BLOCK_HEIGHT, origin.getY() + y * BLOCK_HEIGHT);
	pWindow->draw(*pBlockSprite);
}

// draw the gameboard blocks on the window
//   iterate through each row & col, use drawBlock() to
//   draw a block if it it isn't empty.
void TetrisGame::drawGameboard() {
	for(int x = 0; x < board.MAX_X; x++) {
		for(int y = 0; y < board.MAX_Y; y++) {
				drawBlock(x, y, PURPLE, gameboardOffset);
		}
	}
}

// draw a tetromino on the window
//	 iterate through each mapped loc & drawBlock() for each.
//   the origin determines a 'base point' from which to calculate block offsets
//   If the Tetromino is on the gameboard: use gameboardOffset (otherwise you
//   can specify another point as the origin - for the nextShape)
void TetrisGame::drawTetromino(GridTetromino tetromino, Point origin) {

}

// set the score, update the score display
// form a string "score: ##" to include the current score
// user scoreText.setString() to display it.
void TetrisGame::setScore(int score) {

}

// State & gameplay/logic methods ================================

// return true if shape is within borders (isShapeWithinBorders())
//	 and doesn't intersect locked blocks (doesShapeIntersectLockedBlocks)
bool TetrisGame::isPositionLegal(const GridTetromino &shape) {
	return true;
}

// return true if the shape is within the left, right,
//	 and lower border of the grid. (false otherwise)
bool TetrisGame::isShapeWithinBorders(const GridTetromino &shape) {
	return true;
}

// return true if the grid content at any of the shape's mapped block locs
//   contains anything other than Gameboard::EMPTY_BLOCK. (false otherwise)
//   hint Use Gameboard's areLocsEmpty() for this.
bool TetrisGame::doesShapeIntersectLockedBlocks(const GridTetromino &shape) {
	return true;
}

// set secsPerTick
//   - basic: use MAX_SECS_PER_TICK
//   - advanced: base it on score (higher score results in lower secsPerTick)
void TetrisGame::determineSecsPerTick() {

}
