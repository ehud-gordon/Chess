// Queen.cpp
// Created by hassid on 1/3/18.
//

#include "Queen.h"

const std::string Queen::QUEEN_PRINT = "\u265B";

/**
 * returns a vector with the places we want to move
 * @param pos current position
 * @param dest desired position
 * @return vector with the places we want to move
 */
const std::vector<PosVar> Queen::move(PosVar pos, PosVar dest) const
{
    std::vector<PosVar> moves;

    if (pos.first == dest.first || pos.second == dest.second) // moves like rook
    {
        Piece::_verOrHorMove(pos, dest, moves);
    }
    else if ((dest.second - dest.first) == (pos.second - pos.first) ||
             (dest.second + dest.first) == (pos.second + pos.first)) // moves like bishop
    {
        Piece::_diagonalMove(pos, dest, moves);
    }

    return moves;
}

/** @brief get all possible moves from given pos of a piece */
const std::vector<PosVar> Queen::getAllMoves(PosVar pos) const
{
    std::vector<PosVar> moves;
    for (int row = 1; row <= NUM_OF_ROWS; ++row)
    {
    	if (row != pos.second)
    	{
    		moves.push_back(PosVar(pos.first, row));
    	}
		for (char col = FIRST_COL; col <= LAST_COL; ++col)
		{
			if ( (col != pos.first) && (std::abs(row - pos.second) == std::abs(col - pos.first)) )
			{
    			moves.push_back(PosVar(col, row));
    		}
    		if ( (row == pos.second) && (col != pos.first) )
    		{
    			moves.push_back(PosVar(col, row));
    		}
    	}
    }
    return moves;
}

/**
    * @return a print representation of the Knight. first place - color, second - the string of the Knight
    */
std::pair <Color, std::string> Queen::getPrint() const
{
    return std::make_pair (_color, QUEEN_PRINT);
};
