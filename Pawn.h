// Pawn.h
// Created by hassid on 1/3/18.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

/** Class representing the piece Pawn in chess game */
class Pawn: public Piece 
{
public:
    
    /**
    * using Piece constractor.
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
    * @return a print representation of the pawn. first place - color, sec - the string of the pawn
    */
    std::pair <Color, std::string> getPrint() const override;
    
	/** 
	* @param pos location of pawn
	* @param dest destination of pawn eat move
	* @return true if pawn can eat at dest, false otherwise
	*/
    bool isEatOption(PosVar pos, PosVar dest) const;

private:
	const static std::string PAWN_PRINT;
};

#endif //CHESS_PAWN_H

