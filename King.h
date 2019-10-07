// King.h
// Created by hassid on 1/3/18.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"

/** Class representing the piece King at a chess game. */
class King: public Piece 
{
public:
    /**
     * for using same constructor.
     */
    using Piece::Piece;

    /**
     * returns a vector with the places we want to move
     * @param pos current position
     * @param dest desired position
     * @return vector with the places we want to move
     */
    const std::vector<PosVar> move(PosVar pos, PosVar dest) const override;

    /**
    * @return a print representation of the King. first place - color, sec - the string of the King
    */
    std::pair <Color, std::string> getPrint() const override;

    /** get all possible moves from given pos of a piece
    * @param pos the current position of the piece
    * @return a vector containing all possible positions
    */
    const std::vector<PosVar> getAllMoves(PosVar pos) const override;

    /** updates the moved be true */
    void setMoved(bool flag);

    /** returns if moved */
    bool getMoved() const;

private:
    const static std::string KING_PRINT;
    bool _moved;
};

#endif //CHESS_KING_H
