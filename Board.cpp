// Board.cpp
#include "Board.h"

// ----------------------_board constructor-----------------------------------------//
// Important to note - this isn't VLA, as vectors use std::allocator which allocates on the heap
/** constructs a board*/
Board::Board() : _board(NUM_OF_CELLS), _lastBoard(NUM_OF_CELLS) {}


//---------------------------------board pieces functions------------------------------//
/** add a piece to the board */
void Board::addPiece(PosVar pos, Piece* piecePtr)
{
	int index = _fromPosVarToInt(pos);
	_board[index] = piecePtr;
}

/** moves piece from one place to another */ 
void Board::movePiece(PosVar source, PosVar dest)
{
	int start, end;
	start = _fromPosVarToInt(source);
	Piece* piece = _board[start];
	_board[start] = nullptr;
	
	end = _fromPosVarToInt(dest);
	_board[end] = piece;
}

/** updates board to make a move permanent. Use this only after sure move is legal */ 
void Board::updateBoard()
{
	_lastBoard = _board;
}

/** removes piece from a given location */
void Board::removePiece(PosVar pos)
{
	int index = _fromPosVarToInt(pos);
	_board[index] = nullptr;
}

/** reverses the consquences of the last (and only last) call  to movePiece */ 
void Board::reverseMove()
{
	_board = _lastBoard;
}

//--------------------------------_board check functions-----------------------------//
	
/** return pointer to the piece at a given location, nullptr if there's any */
Piece* Board::getPiece(PosVar pos)
{
	int index = _fromPosVarToInt(pos);
	return _board[index];
}

/** return pointer to the piece at a given location, nullptr if there's any */
const Piece* Board::getPiece(PosVar pos) const
{
	int index = _fromPosVarToInt(pos);
	return _board[index];
}

/**  checks that all the cells in the given container (except last one) are empty */
bool Board::isRangeEmpty(std::vector<PosVar>& cells) const
{
	for (std::vector<PosVar>::iterator it = cells.begin(); it != cells.end()-1; ++it)
	{
		int index = _fromPosVarToInt(*it);
		if (_board[index] != nullptr)
		{
			return false;
		}
	}
	return true;
}
	
/** checks that a given coordinates are in the board range */
bool Board::inRange(PosVar pos)
{
	return  (pos.first >= FIRST_COL) && (pos.first <= LAST_COL) && (pos.second >= FIRST_ROW)
			&& (pos.second <= LAST_ROW);
}

/** return all positions on board of pieces that return true to given Pred */
std::vector<PosVar> Board::getPosIf(bool (*Pred)(Piece*)) const
{
	std::vector<PosVar> positions;
	for (int i = 0; i < NUM_OF_CELLS; ++i)
	{
        if ( (_board[i] != nullptr) && (*Pred)(_board[i]) )
		{
			PosVar pos = _fromIntToPosVar(i);
			positions.push_back(pos);
		}
	}
	return positions;
}

/** return all positions and pointers of pieces that return true to given Pred */
std::vector<std::pair<Piece*, PosVar>> Board::getPointersAndPosIf(bool (*Pred)(Piece*)) const
{
	std::vector<std::pair<Piece*, PosVar>> result;
	for (int i = 0; i < NUM_OF_CELLS; ++i)
	{
        if ( (_board[i] != nullptr) && (*Pred)(_board[i]) )
		{
			PosVar pos = _fromIntToPosVar(i);
			result.push_back(std::make_pair(_board[i], pos));
		}
	}
	return result;
}

// ----------------------------BOARD HELPER FUNCTIONS--------------------------------------//

/** converts from <Col><Row> representation to board representation */
int Board::_fromPosVarToInt(PosVar pos)
{
	int index = (pos.second - 1) * NUM_OF_COLS + (pos.first - FIRST_COL);
	return index;
}


/** converts from board representation to <Col><Row> */
PosVar Board::_fromIntToPosVar(int index)
{
	char col = (index % NUM_OF_COLS) + FIRST_COL;
	int row = (index / NUM_OF_COLS) + 1;
	
	return PosVar(col, row);
}

/**
* helper function for drawBoard
* @return a string containing all the column names
*/
std::string getColumnNames()
{
	std::string colNames;
	for (char col = FIRST_COL; col <= LAST_COL; ++col)
	{
		colNames.push_back(col);
	}
	return colNames;
}


/** draws the board */
std::ostream& operator<<(std::ostream& os, const Board& board)
{
	PosVar pos;
	std::string code;
	std::string background;
	std::string text;
	os << "  " + getColumnNames() + "\n\n";
	for (pos.second = NUM_OF_ROWS; pos.second >= 1; --pos.second)
	{
		os << pos.second  <<  " "; // print row number at the left side
		for (pos.first = FIRST_COL; pos.first <= LAST_COL; ++pos.first)
		{
			if (board.getPiece(pos) == nullptr)
			{
				code = " ";
				text = "0";
			}
			else
			{
				std::pair<Color, const std::string> toPrint = (board.getPiece(pos))->getPrint();
				text = ((toPrint.first == WHITE)? WHITE_TEXT: BLACK_TEXT);
				code = toPrint.second;
			}
			background = ((pos.second  + pos.first) % 2? BLUE_BACK: GREEN_BACK);
			os << "\33[" + text + ";" + background + "m" + code + "\33[0m"; // print _board place
		}
		os << " " << pos.second  << "\n"; // print row number at the right side
	}
		os << "\n  " + getColumnNames() + "\n\n"; // Print ABCDEFGH
	return os;
}

