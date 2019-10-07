// Constants.h
#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#include <iostream>

const static int FIRST_ROW = 1;
const static int LAST_ROW = 8;
const static int NUM_OF_ROWS = 8;

const static char FIRST_COL = 'A';
const static int NUM_OF_COLS = 8;
const static char LAST_COL = FIRST_COL + NUM_OF_COLS - 1;

const static int NUM_OF_CELLS = NUM_OF_ROWS * NUM_OF_COLS;


typedef std::pair<char, int> PosVar; /** @typedef a Type representating a position <Col><Row>*/

/**
* @enum Color the colors of the pieces
*/
enum Color
{
	WHITE,
	BLACK
};


/**
* @enum Type the type of the piece. We set KNIGHT to 3 because there we need two rooks.
*/
enum Type
{
	PAWN,
	ROOK,
	KNIGHT = 3,
	BISHOP,
	QUEEN,
	KING
};

#endif

