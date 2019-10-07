// Rook.h
// Created by hassid on 1/3/18.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Piece.h"

/** Class representing the piece Rook at chess Game.*/
class Rook: public Piece 
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
    * @return a print representation of the rook. first place - color, sec - the string of the rook
    */
    std::pair <Color, std::string> getPrint() const override;

    /** updates the move to given flag */
    void setMoved(bool flag);

    /** returns if moved */
    bool getMoved() const;

private:

    const static std::string ROOK_PRINT; /* the code print of this piece */

    bool _moved;
};

#endif //CHESS_ROOK_H
