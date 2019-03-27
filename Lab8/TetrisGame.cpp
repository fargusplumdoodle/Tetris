#include "TetrisGame.h"

// destructor, set pointers to null
//~TetrisGame::TetrisGame() {


TetrisGame::TetrisGame(sf::RenderWindow *window, sf::Sprite *blockSprite, Point gameboardOffsets, Point nextShapeOffsets) {
	//   assign pointers,
	pWindow = window;
	pBlockSprite = blockSprite;
	gameboardOffset = gameboardOffsets;
	nextShapeOffset = nextShapeOffsets;
	//   load font from file: fonts/RedOctober.ttf
	scoreFont.loadFromFile("fonts/RedOctober.ttf");
	//   setup scoreText
	scoreText.setFont(scoreFont);
	setScore(score);

	//TODO: REMOVE THIS
	currentShape.setShape(currentShape.getRandomShape());
	currentShape.setGridLoc(board.getSpawnLoc());
	board.setContent((Gameboard::MAX_X / 2),  Gameboard::MAX_Y / 2, 1);
	//   reset the game
	reset();
}

// draw anything to do with the game,
// includes board, currentShape, nextShape, score
void TetrisGame::draw(){
	drawTetromino(currentShape, currentShape.getGridLoc());
	drawGameboard();
}

// Event and game loop processing
// handles keypress events (up, left, right, down, space)
void TetrisGame::onKeyPressed(sf::Event event){
	// handling rotation
	switch (event.key.code) {
		case sf::Keyboard::Up:
			attemptRotate(currentShape);
			break;
		case sf::Keyboard::Left:
			attemptMove(currentShape, -1, 0);
			break;
		case sf::Keyboard::Right:
			attemptMove(currentShape, 1, 0);
			break;
		case sf::Keyboard::Space:
			drop(currentShape);
			lock(currentShape);
			break;
	}
}

// called every game loop to handle ticks & tetromino placement (locking)
void TetrisGame::processGameLoop(float secondsSinceLastLoop){
	if (secondsSinceLastTick >= secsPerTick) {
		tick();
	}
	else {
		secondsSinceLastTick += secondsSinceLastLoop;
	}
}

// A tick() forces the currentShape to move (if there were no tick,
// the currentShape would float in position forever). This should
// call attemptMove() on the currentShape.  If not successful, lock() 
// the currentShape (it can move no further), and record the fact that a
// shape was placed (using shapePlacedSinceLastGameLoop)
void TetrisGame::tick() {
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
	}
	secondsSinceLastTick = 0;
}

	// reset everything for a new game (use existing functions) 
	//  - setScore to 0
	//  - determineSecondsPerTick(),
	//  - clear the gameboard,
	//  - pick & spawn next shape
	//  - pick next shape again
void TetrisGame::reset(){}
	// assign nextShape.setShape a new random shape  
void TetrisGame::pickNextShape(){
	nextShape.setShape(nextShape.getRandomShape());
}


	// copy the nextShape into the currentShape and set 
	//   its loc to be the gameboard's spawn loc.
	//	 - return true/false based on isPositionLegal()
bool TetrisGame::spawnNextShape() { return true; }



	// test if a rotation is legal on the tetromino, 
	//   if so, rotate it.
	//  To do this:
	//	 1) create a (local) temporary copy of the tetromino
	//	 2) rotate it (shape.rotateCW())
	//	 3) test if temp rotatio was legal (isPositionLegal()), 
	//      if so - rotate the original tetromino.
	//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptRotate(GridTetromino &shape) { 

	GridTetromino tmp = shape;
	tmp.rotateCW();

	if (isPositionLegal(tmp)) {
		shape.rotateCW();
		return true;
	} 
	return false; 
}


	// test if a move is legal on the tetromino, if so, move it.
	//  To do this:
	//	 1) create a (local) temporary copy of the current shape
	//	 2) move it (temp.move())
	//	 3) test if temp move was legal (isPositionLegal(),
	//      if so - move the original.
	//	 4) return true/false to indicate successful movement
bool TetrisGame::attemptMove(GridTetromino &shape, int x, int y) { 
	GridTetromino tmp = shape;
	tmp.move(x, y);

	if (isPositionLegal(tmp)) {
		shape.move(x, y);
		return true;
	}

	return false;
}


	// drops the tetromino vertically as far as it can 
	//   legally go.  Use attemptMove(). This can be done in 1 line.
void TetrisGame::drop(GridTetromino &shape){
	for (int i = 0; i <= Gameboard::MAX_Y; i++) {
		if (! attemptMove(currentShape, 0, 1)) {
			break;
		}		
	}
}

	// copy the contents of the tetromino's mapped block locs to the grid.
	//	 1) get current blockshape locs via tetromino.getBlockLocsMappedToGrid()
	//	 2) iterate on the mapped block locs and copy the contents (color) 
	//      of each to the grid (via gameboard.setGridContent()) 
void TetrisGame::lock(const GridTetromino &shape) {
	// std::cout << static_cast<int>(shape.getColor()) << std::endl;
	board.setContent(shape.getBlockLocsMappedToGrid(), static_cast<int>(shape.getColor()));
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
void TetrisGame::drawBlock(int x, int y, TetColor color, Point origin){
	//1
	pBlockSprite->setTextureRect(sf::IntRect((static_cast<int>(color) * BLOCK_WIDTH), 0, BLOCK_WIDTH, BLOCK_HEIGHT));
	//2
	pBlockSprite->setPosition((float) (origin.getX() + (x * BLOCK_WIDTH)), (float) (origin.getY() + (y * BLOCK_HEIGHT)));
	//3
	pWindow->draw(*pBlockSprite);
}

	// draw the gameboard blocks on the window
	//   iterate through each row & col, use drawBlock() to 
	//   draw a block if it it isn't empty.
void TetrisGame::drawGameboard(){
	for (int y = 0; y < Gameboard::MAX_Y; y++) {
		for (int x = 0; x < Gameboard::MAX_X; x++) {
			if (board.getContent(x, y) != Gameboard::EMPTY_BLOCK) {
				drawBlock(x, y, TetColor::YELLOW, gameboardOffset);
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
		std::vector<Point> blocks = tetromino.getBlockLocs();
		Point offSetOrigin = Point((origin.getX() * BLOCK_WIDTH) + gameboardOffset.getX(), (origin.getY() * BLOCK_HEIGHT) + gameboardOffset.getY());

		
		//	 iterate through each mapped loc & drawBlock() for each.
		for (int i = 0; i < blocks.size(); i++) {
			drawBlock(blocks[i].getX(), blocks[i].getY(), tetromino.getColor(), offSetOrigin);
		}
}

	// set the score, update the score display
	// form a string "score: ##" to include the current score
	// user scoreText.setString() to display it.
void TetrisGame::setScore(int score) {
	std::string label = "score: " + score;
	scoreText.setString(label);
}

	// State & gameplay/logic methods ================================

	// return true if shape is within borders (isShapeWithinBorders())
	//	 and doesn't intersect locked blocks (doesShapeIntersectLockedBlocks)
bool TetrisGame::isPositionLegal(const GridTetromino &shape) { 
	if (!isShapeWithinBorders(shape)) { return false; }
	if (!doesShapeIntersectLockedBlocks(shape)) { return false; }
	return true;
}

	// return true if the shape is within the left, right,
	//	 and lower border of the grid. (false otherwise)
bool TetrisGame::isShapeWithinBorders(const GridTetromino &shape) {
	std::vector<Point> blocks = shape.getBlockLocsMappedToGrid();
	for (int i = 0; i < blocks.size(); i++) {
		if ((blocks[i].getX() >= board.MAX_X) || (blocks[i].getX() < 0)) {
			return false; }
		if ((blocks[i].getY() >= board.MAX_Y) || (blocks[i].getY() < 0)) {
			return false; }
	}
	return true;
	}

	// return true if the grid content at any of the shape's mapped block locs	
	//   contains anything other than Gameboard::EMPTY_BLOCK. (false otherwise)	
	//   hint Use Gameboard's areLocsEmpty() for this.
bool TetrisGame::doesShapeIntersectLockedBlocks(const GridTetromino &shape) {
	return board.areLocsEmpty(shape.getBlockLocsMappedToGrid());
}

	// set secsPerTick 
	//   - basic: use MAX_SECS_PER_TICK
	//   - advanced: base it on score (higher score results in lower secsPerTick)
void TetrisGame::determineSecsPerTick(){}