// Pawn.cpp
// Created by hassid on 1/3/18.
//

#include "Pawn.h"

const std::string Pawn::PAWN_PRINT = "\u265F";

/**
 * returns a vector with the places we want to move
 * @param pos current position
 * @param dest desired position
 * @return vector with the places we want to move
 */
const std::vector<PosVar> Pawn::move(PosVar pos, PosVar dest) const
{
    std::vector<PosVar> moves;
	
	if (pos.first != dest.first)
	{
		return moves;
	}
	
    if (_color == WHITE && pos.second == 2 && pos.second + 2 == dest.second) //checks first move white
    {
        pos.second += 1;
        moves.push_back(pos);
    }
    else if (_color == BLACK && pos.second == 7 && pos.second - 2 == dest.second) //checks first move black
    {
        pos.second -= 1;
        moves.push_back(pos);
    }

    if ( (_color == WHITE && (pos.second + 1 != dest.second)) ||
         (_color == BLACK && (pos.second - 1 != dest.second)) )
    {
        return moves;
    }

    moves.push_back(dest);
    return moves;
}

/** @brief get all possible moves from given pos of a piece*/
const std::vector<PosVar> Pawn::getAllMoves(PosVar pos) const
{
    std::vector<PosVar> moves;
    if (_color == WHITE)
    {
    	moves.push_back(PosVar(pos.first, pos.second + 1));
    	moves.push_back(PosVar(pos.first, pos.second + 2));
    	moves.push_back(PosVar(pos.first + 1, pos.second + 1));
    	moves.push_back(PosVar(pos.first - 1, pos.second + 1));
    }
    else
    {
    	moves.push_back(PosVar(pos.first, pos.second - 1));
    	moves.push_back(PosVar(pos.first, pos.second - 2));
    	moves.push_back(PosVar(pos.first + 1, pos.second - 1));
    	moves.push_back(PosVar(pos.first - 1, pos.second - 1));
    }
    return moves;
}

/**
* @return a print representation of the pawn. first place - color, sec - the string of the pawn
*/
std::pair<Color, std::string> Pawn::getPrint() const
{
	return std::make_pair (_color, PAWN_PRINT);
};

/** checks if a pawn positioned at pos can make eat move to dest */
bool Pawn::isEatOption(PosVar pos, PosVar dest) const
{
    if (std::abs(pos.first - dest.first) == 1)
    {
        if (_color == WHITE)
        {
        	return (pos.second + 1 == dest.second);
        }
        else
        {
            return (pos.second - 1 == dest.second);
        }
    }
    return false;
}


