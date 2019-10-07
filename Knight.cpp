// Knight.cpp
// Created by hassid on 1/3/18.
//

#include "Knight.h"

const std::string Knight::KNIGHT_PRINT = "\u265E";

/**
 * returns a vector with the places we want to move
 * @param pos current position
 * @param dest desired position
 * @return vector with the places we want to move
 */
const std::vector<PosVar> Knight::move(PosVar pos, PosVar dest) const
{
    std::vector<PosVar> moves;

    if (abs(dest.first - pos.first) == 1 && abs(dest.second - pos.second) == 2)
    {
        moves.push_back(dest);
    }
    else if (abs(dest.first - pos.first) == 2 && abs(dest.second - pos.second) == 1)
    {
        moves.push_back(dest);
    }
    return moves;
}

/** @brief get all possible moves from given pos of a piece */
const std::vector<PosVar> Knight::getAllMoves(PosVar pos) const
{
    std::vector<PosVar> moves;
    for (int row = pos.second - 2; row <= pos.second + 2; ++row)
    {
		if (row != pos.second)
		{
			if (std::abs(row - pos.second) == 2)
			{
				moves.push_back(PosVar(pos.first - 1, row));
				moves.push_back(PosVar(pos.first + 1, row));
			}
			else
			{
				moves.push_back(PosVar(pos.first - 2, row));
				moves.push_back(PosVar(pos.first + 2, row));				
			}
		}
    }
    return moves;
}

/**
    * @return a print representation of the Knight. first place - color, second - the string of the Knight
    */
std::pair <Color, std::string> Knight::getPrint() const
{
    return std::make_pair (_color, KNIGHT_PRINT);
};
