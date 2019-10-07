// Rook.cpp
// Created by hassid on 1/3/18.
//


#include "Rook.h"

const std::string Rook::ROOK_PRINT = "\u265C"; /* the code print of this piece */

/**
 * returns a vector with the places we want to move
 * @param pos current position
 * @param dest desired position
 * @return vector with the places we want to move
 */
const std::vector<PosVar> Rook::move(PosVar pos, PosVar dest) const
{
    std::vector<PosVar> moves;

    if (pos.first != dest.first && pos.second != dest.second)
    {
        return moves;
    }
    Piece::_verOrHorMove(pos, dest, moves);
    return moves;
}

/** @brief get all possible moves from given pos of a piece */
const std::vector<PosVar> Rook::getAllMoves(PosVar pos) const
{
    std::vector<PosVar> moves;
    for (int row = 1; row <= NUM_OF_ROWS; ++row)
    {
    	if (row != pos.second)
    	{
    		moves.push_back(PosVar(pos.first, row));
    	}
	}
	for (char col = FIRST_COL; col <= LAST_COL; ++col)
	{
		if (col != pos.first)
    	{
    		moves.push_back(PosVar(col, pos.second));
    	}
	}
    return moves;
}

/**
    * @return a print representation of the rook. first place - color, second - the string of the rook
    */
std::pair <Color, std::string> Rook::getPrint() const
{
    return std::make_pair (_color, ROOK_PRINT);
};


/** updates the move to given flag */
void Rook::setMoved(bool flag)
{
    _moved = flag;
}

/** returns if moved */
bool Rook::getMoved() const
{
    return _moved;
}
