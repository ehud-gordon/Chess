// Board.h
#ifndef _BOARD_H
#define _BOARD_H

//--------------------------------------INCLUDES--------------------------------------------//
#include "Piece.h"
#include "Constants.h"
#include <utility>

//-----------------------------------CONSTANTS--------------------------------------------//
const static std::string BLACK_TEXT = "30"; /** Code for printing black pieces */
const static std::string WHITE_TEXT = "37"; /** Code for printing white pieces */
const static std::string NORM_TEXT = "0"; /** code for printing cells with no pieces */
const static std::string BLUE_BACK = "46"; 
const static std::string GREEN_BACK = "42";
const static std::string RED_BACK = "41";



//-----------------------------------CLASS DECLARATION-----------------------------------------//
/**
* A Board class, composed with pieces, that gets and returns information about pieces positions
*/ 
class Board
{
public:
	/** empty constructor */
	Board();
	
//------------------------Board pieces functions-------------------------------------//
	
	/** add a piece to the board
	* @param pos the place in the board to add, in fomrat <Col><Row>
	* @param piecePtr a pointer to the Piece object to be added
	*/
	void addPiece(PosVar pos, Piece* piecePtr);

	/** moves a piece on the board
	* @param current location of piece
	* @param destination
	*/
	void movePiece(PosVar source, PosVar dest);

	/** makes a move permanent */
	void updateBoard();

	/** removes a piece from the board
	* @param pos - location of piece to be removed
	*/
	void removePiece(PosVar pos);
	
	/** undo the last (and only last) call to movePiece*/
	void reverseMove();
	
// --------------------------Board check functions-------------------------------------//

	/**
	* @param pos location to be checked
	* @return pointer to the piece at a given location, nullptr if there's any
	*/
	Piece* getPiece(PosVar pos);

    /** const version of getPiece() functions */
	const Piece* getPiece(PosVar pos) const;

	/**  checks that all the cells in the given container (except last one) are empty
	* @param cells container of positions to be checked
	* @return true if location from the first up to one before last don't have any pieces in them
	*/
	bool isRangeEmpty(std::vector<PosVar>& cells) const;

	/**
	* @param pos coordinates matching the board format: <Column><Row>
	* @return true if the board contains those coordinates, false otherwise
	*/ 
	static bool inRange(PosVar pos);
	
	/** return all positions and pointers of pieces that return true to given Pred
	* @param Pred a pointer to function that recieves a Piece pointer and returns a bool
	* @return vector containing all positions and pointers that returned true to Pred
	*/
	std::vector<PosVar> getPosIf(bool (*Pred)(Piece*)) const;
	
	/** return all positions and pointers of pieces that return true to given Pred
	* @param Pred a pointer to function that recieves a Piece pointer and returns a bool
	* @return vector containing all positions that returned true to Pred
	*/
	std::vector<std::pair<Piece*, PosVar>> getPointersAndPosIf(bool (*Pred)(Piece*)) const;

	/**
	* draws the board
	* @param os the output stream into which we will draw
	* @param board the board to be printed
	* @return the outputsream after we've used it
	*/
	friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
	std::vector<Piece*> _board;
	std::vector<Piece*> _lastBoard; // used for reverse move
	
	/** converts from <Col><Row> representation to board representation
	* @param coordinates in the board format <Column><Row>
	* @return the conversion of the given coordinates to where the board stores them
	*/ 
	static int _fromPosVarToInt(PosVar pos);
	
	
	/** converts from board representation to <Col><Row>
	* @param internal representation of cell in the board
	* @return the representation in the format of <Column><Row>
	*/ 
	static PosVar _fromIntToPosVar(int pos);		
};

#endif

