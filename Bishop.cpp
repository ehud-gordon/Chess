// Bishop.cpp
// Created by hassid on 1/3/18.

#include "Bishop.h"

const std::string Bishop::BISHOP_PRINT = "\u265D";

/** @brief check if dest is reachable for piece */
const std::vector<PosVar> Bishop::move(PosVar pos, PosVar dest) const
{
    std::vector<PosVar> moves;

    if ((dest.second - dest.first) != (pos.second - pos.first) &&
        (dest.second + dest.first) != (pos.second + pos.first) )
    {
        return moves;
    }
    Piece::_diagonalMove(pos, dest, moves);

    return moves;
}

/** @brief get all possible moves from given pos of a piece */
const std::vector<PosVar> Bishop::getAllMoves(PosVar pos) const
{
    std::vector<PosVar> moves;
    for (int row = 1; row <= NUM_OF_ROWS; ++row)
    {
		for (char col = FIRST_COL; (row != pos.second) && (col <= LAST_COL); ++col)
		{
			if ( (col != pos.first) && (std::abs(row - pos.second) == std::abs(col - pos.first)) )
			{
    			moves.push_back(PosVar(col, row));
    		}
    	}
    }
    return moves;
}

/**
* @return a print representation of the king. first place - color, sec - the string of the king
*/
std::pair <Color, std::string> Bishop::getPrint() const
{
    return std::make_pair (_color, BISHOP_PRINT);
};

