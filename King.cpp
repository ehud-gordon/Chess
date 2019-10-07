// King.cpp
// Created by hassid on 1/3/18.
//

#include "King.h"

const std::string King::KING_PRINT = "\u265A";

/**
 * returns a vector with the places we want to move
 * @param pos current position
 * @param dest desired position
 * @return vector with the places we want to move
 */
const std::vector<PosVar> King::move(PosVar pos, PosVar dest) const
{
    std::vector<PosVar> moves;

    if (abs(dest.first - pos.first) <= 1 && abs(dest.second - pos.second) <= 1)
    {
        moves.push_back(dest);
    }

    return moves;
}

/**
* @return a print representation of the king. first place - color, sec - the string of the king
*/
std::pair <Color, std::string> King::getPrint() const
{
    return std::make_pair(_color, KING_PRINT);
};

/** @brief get all possible moves from given pos of a piece */
const std::vector<PosVar> King::getAllMoves(PosVar pos) const
{
    std::vector<PosVar> moves;
    for (char col = (pos.first - 1); col <= (pos.first + 1); col++)
    {
        for (int row = (pos.second - 1); row <= (pos.second + 1); row++)
        {
            if ( (col != pos.first) || (row != pos.second) )
            {
	            moves.push_back(PosVar(col, row));
            }
        }
    }
    return moves;
}

/** updates moved to given flag */
void King::setMoved(bool flag)
{
    _moved = flag;
}

/** returns if moved */
bool King::getMoved() const
{
    return _moved;
}
