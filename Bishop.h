// Bishop.h
// Created by hassid on 1/3/18.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"

/** Class representing the Bishop piece in chess */
class Bishop: public Piece 
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
    
    /** get all possible moves from given pos of a piece
    * @param pos the current position of the piece
    * @return a vector containing all possible positions
    */
	const std::vector<PosVar> getAllMoves(PosVar pos) const override;
	
    /**
    * @return a print representation of the Bishop. first place - color, sec - the string of the Bishop
    */
    std::pair <Color, std::string> getPrint() const override;

private:
    const static std::string BISHOP_PRINT;
};

#endif //CHESS_BISHOP_H

