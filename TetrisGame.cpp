//
// Created by Brendon Waters on 2019-03-25.
//

#include "TetrisGame.h"
using namespace std;

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
	reset();

	scoreFont.loadFromFile("fonts/RedOctober.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(435, 325);
}


// destructor, set pointers to null
TetrisGame::~TetrisGame() {
	pWindow = nullptr;
	pBlockSprite = nullptr;
}

// draw anything to do with the game,
// includes board, currentShape, nextShape, score
void TetrisGame::draw() {
	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	pWindow->draw(scoreText);
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
void TetrisGame::onKeyPressed(sf::Event event) {
	switch (event.key.code) {
		case sf::Keyboard::Up : attemptRotate(currentShape);
		break;
		case sf::Keyboard::Left : attemptMove(currentShape, -1, 0);
		break;
		case sf::Keyboard::Right : attemptMove(currentShape, 1, 0);
		break;
		case sf::Keyboard::Space : drop(currentShape); lock(currentShape); shapePlacedSinceLastGameLoop = true;
		break;
		case sf::Keyboard::Down :
			if(!attemptMove(currentShape, 0, 1)) {
				lock(currentShape);
			} else {
				attemptMove(currentShape, 0, 1);
			};
		};
	}

// called every game loop to handle ticks & tetromino placement (locking)
void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	secondsSinceLastTick += secondsSinceLastLoop;
	if (secondsSinceLastTick > secsPerTick) {
		tick();
		secondsSinceLastTick -= secsPerTick;
	}
	if (shapePlacedSinceLastGameLoop) {
		if (!spawnNextShape()) {
			reset();
		} else {
			pickNextShape();
			score += board.removeCompletedRows();
			setScore(score);
			determineSecsPerTick();
			shapePlacedSinceLastGameLoop =  false;

		}
	}
}

// A tick() forces the currentShape to move (if there were no tick,
// the currentShape would float in position forever). This should
// call attemptMove() on the currentShape.  If not successful, lock()
// the currentShape (it can move no further), and record the fact that a
// shape was placed (using shapePlacedSinceLastGameLoop)
void TetrisGame::tick() {
	if (attemptMove(currentShape, 0, 1)) {
	} else {
		lock(currentShape);
		shapePlacedSinceLastGameLoop = true;
	}
}

// reset everything for a new game (use existing functions)
//  - setScore to 0
//  - determineSecondsPerTick(),
//  - clear the gameboard,
//  - pick & spawn next shape
//  - pick next shape again
void TetrisGame::reset() {
	score  =  0;
	setScore(score);
	determineSecsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();
	shapePlacedSinceLastGameLoop =  false;

}

// assign nextShape.setShape a new random shape
void TetrisGame::pickNextShape() {
	nextShape.setShape(Tetromino::getRandomShape());

}


// copy the nextShape into the currentShape and set
//   its loc to be the gameboard's spawn loc.
//	 - return true/false based on isPositionLegal()
bool TetrisGame::spawnNextShape() {
	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());
	return isPositionLegal(currentShape);
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
	GridTetromino tempTet = shape;
	tempTet.rotateCW();
	if (isPositionLegal(tempTet)) {
		shape.rotateCW();
		return true;
	} else {
		return false;
	}
}


// test if a move is legal on the tetromino, if so, move it.
//  To do this:
//	 1) create a (local) temporary copy of the current shape
//	 2) move it (temp.move())
//	 3) test if temp move was legal (isPositionLegal(),
//      if so - move the original.
//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptMove(GridTetromino &shape, int x, int y) {
	GridTetromino tempTet = shape;
	tempTet.move(x, y);
	if (isPositionLegal(tempTet)) {
		shape.move(x, y);
		return true;
	} else {
		return false;
	}
}


// drops the tetromino vertically as far as it can
//   legally go.  Use attemptMove(). This can be done in 1 line.
void TetrisGame::drop(GridTetromino &shape) {
	while (attemptMove(shape, 0, 1));
}

// copy the contents of the tetromino's mapped block locs to the grid.
//	 1) get current blockshape locs via tetromino.getBlockLocsMappedToGrid()
//	 2) iterate on the mapped block locs and copy the contents (color)
//      of each to the grid (via gameboard.setGridContent())
void TetrisGame::lock(const GridTetromino &shape) {
	for (auto contents : shape.getBlockLocsMappedToGrid()) {
		board.setContent(contents, shape.getColor());
	}
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
			if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) {
				drawBlock(x, y, static_cast<TetColor>(board.getContent(x, y)) , gameboardOffset);
			}
		}
	}
}

// draw a tetromino on the window
//	 iterate through each mapped loc & drawBlock() for each.
//   the origin determines a 'base point' from which to calculate block offsets
//   If the Tetromino is on the gameboard: use gameboardOffset (otherwise you
//   can specify another point as the origin - for the nextShape)
void TetrisGame::drawTetromino(GridTetromino tetromino, Point origin) {
	for (auto loc : tetromino.getBlockLocsMappedToGrid()) {
		drawBlock(loc.getX(), loc.getY(), tetromino.getColor(), origin);
	}
}

// set the score, update the score display
// form a string "score: ##" to include the current score
// user scoreText.setString() to display it.
void TetrisGame::setScore(int score) {
	scoreText.setString("score: " + to_string(score));
}

// State & gameplay/logic methods ================================

// return true if shape is within borders (isShapeWithinBorders())
//	 and doesn't intersect locked blocks (doesShapeIntersectLockedBlocks)
bool TetrisGame::isPositionLegal(const GridTetromino &shape) {
	if (isShapeWithinBorders(shape) && doesShapeIntersectLockedBlocks(shape)) {
		return true;
	} else {
		return false;
	}
}

// return true if the shape is within the left, right,
//	 and lower border of the grid. (false otherwise)
bool TetrisGame::isShapeWithinBorders(const GridTetromino &shape) {
	for (auto loc : shape.getBlockLocsMappedToGrid()) {
		if (loc.getX() < board.MAX_X && loc.getX() >= 0 && loc.getY() < board.MAX_Y && loc.getY() >= -4) {
		} else {
			return false;
		}
	}
	return true;
}

// return true if the grid content at any of the shape's mapped block locs
//   contains anything other than Gameboard::EMPTY_BLOCK. (false otherwise)
//   hint Use Gameboard's areLocsEmpty() for this.
bool TetrisGame::doesShapeIntersectLockedBlocks(const GridTetromino &shape) {
		if (board.areLocsEmpty(shape.getBlockLocsMappedToGrid())) {
			return true;
	} else {
			return false;
		}
}

// set secsPerTick
//   - basic: use MAX_SECS_PER_TICK
//   - advanced: base it on score (higher score results in lower secsPerTick)
void TetrisGame::determineSecsPerTick() {
	secsPerTick = MAX_SECS_PER_TICK;

}
