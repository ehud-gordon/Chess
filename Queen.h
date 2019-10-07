// Queen.h
// Created by hassid on 1/3/18.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

/** Class representing the piece Queen at a chess game. */
class Queen: public Piece 
{
public:
    /**
     * for using same constractor.
     */
    using Piece::Piece;

    /**
     * returns a vector with the places we want to move
     * @param pos current position
     * @param dest desired position
     * @return vector with the places we want to move
     */
    const std::vector<PosVar> move(PosVar pos, PosVar dest) const override;
    
    /** get all possible moves from given pos of a piece
    * @param pos the current position of the piece
    * @return a vector containing all possible positions
    */
	const std::vector<PosVar> getAllMoves(PosVar pos) const override;

    /**
    * @return a print representation of the Queen. first place - color, sec - the string of the Queen
    */
    std::pair <Color, std::string> getPrint() const override;

private:
    const static std::string QUEEN_PRINT;
};

#endif //CHESS_QUEEN_H
