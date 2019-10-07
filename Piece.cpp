// Piece.cpp
// Created by hassid on 1/3/18.
//

#include "Piece.h"

/**
 * @return the color of the piece
 */
Color Piece::getColor() const
{
    return _color;
}

/**
 * @return the type of the piece
 */
Type Piece::getType() const
{
    return _type;
}

/**
 * helper for queen and rook, returns a vertical or horizontal move. assume there is one
 */
void Piece::_verOrHorMove(PosVar pos, PosVar dest, std::vector<PosVar>& moves)
{
    if (pos.first == dest.first)
    {
        if (pos.second < dest.second)
        {
            for(int i = pos.second + 1; i <= dest.second; ++i)
            {
                moves.push_back(PosVar(pos.first, i));
            }
        }
        else
        {
            for(int i = pos.second - 1; i >= dest.second; --i)
            {
                moves.push_back(PosVar(pos.first, i));
            }
        }
    }
    else
    {
        if (pos.first < dest.first)
        {
            for(char i = pos.first + 1; i <= dest.first; ++i)
            {
                moves.push_back(PosVar(i, pos.second));
            }
        }
        else
        {
            for (char i = pos.first - 1; i >= dest.first; --i)
            {
                moves.push_back(PosVar(i, pos.second));
            }
        }
    }
}

/**
 * helper for queen and bishop, returns a diagonal move. assume there is one
 */
void Piece::_diagonalMove(PosVar pos, PosVar dest, std::vector<PosVar>& moves)
{
    if (pos.first < dest.first) //right
    {
        if (pos.second < dest.second) // up
        {
            _mainDiagonal(pos, dest, true, moves);
        }
        else // down
        {
            _secondaryDiagonal(pos, dest, false, moves);
        }
    }
    else // left
    {
        if (pos.second < dest.second) // up
        {
            _secondaryDiagonal(pos, dest, true, moves);
        }
        else // down
        {
            _mainDiagonal(pos, dest, false, moves);
        }
    }
}

/**
 * @brief inserts to moves the coordinates needed in the relavant Diagonal
 */
void Piece::_mainDiagonal(PosVar pos, PosVar dest, bool up, std::vector<PosVar>& moves)
{
    if (up)
    {
        for (int col = pos.first + 1, row = pos.second + 1; col <= dest.first && row <= dest.second ; ++col, ++row)
        {
            moves.push_back(PosVar((char) col, row));
        }
    }
    else
    {
        for (int col = pos.first - 1, row = pos.second - 1; col >= dest.first && row >= dest.second ; --col, --row)
        {
            moves.push_back(PosVar((char) col, row));
        }
    }
}

/**
 * @brief inserts to moves the coordinates needed in the relavant Diagonal
 */
void Piece::_secondaryDiagonal(PosVar pos, PosVar dest, bool up, std::vector<PosVar>& moves)
{
    if (up)
    {
        for (int col = pos.first - 1, row = pos.second + 1; col >= dest.first  && row <= dest.second ; --col, ++row)
        {
            moves.push_back(PosVar((char) col, row));
        }
    }
    else
    {
        for (int col = pos.first + 1, row = pos.second - 1; col <= dest.first && row >= dest.second ; col++, row--)
        {
            moves.push_back(PosVar((char) col, row));
        }
    }
}

