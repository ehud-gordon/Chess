// Piece.h

#ifndef _PIECE_H
#define _PIECE_H

//--------------------------------------INCLUDES--------------------------------------------//

#include <utility>
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include "Constants.h"

//-----------------------------------CLASS DECLARATION-----------------------------------------//

/**
* A Piece class, that checks a move, and contains data (color and print code) 
*/
class Piece
{
public:
	/**
	 * Constractor for piece
	 * @param type the type of the piece
	 * @param color the color of the piece
	 */
	Piece(Type type, Color color): _type(type), _color(color) {}
	
	/**
	* virtual empty destructor
	*/ 
	virtual ~Piece() noexcept {};

	/**
	 * returns a vector with the places we want to move
	 * @param pos current position
	 * @param dest desired position
	 * @return vector with the places we want to move
	 */
	virtual const std::vector<PosVar> move(PosVar pos, PosVar dest) const = 0;
	
    /** get all possible moves from given pos of a piece
    * @param pos the current position of the piece
    * @return a vector containing all possible positions
    */
    virtual const std::vector<PosVar> getAllMoves(PosVar pos) const = 0;
	
	/**
	 * @return the color of the piece
	 */
	Color getColor() const;

	/**
	 * @return the type of the piece
	 */
	Type getType() const;

	/**
	 * @return a print representation of the piece. first place - color, sec - the string of the piece
	 */
	virtual std::pair<Color, std::string> getPrint() const = 0;

protected:
	Type _type;
	Color _color;
	
//-------------------------------------Piece Move Functions-----------------------------------//

	/**
     * @brief inserts to moves the coordinates needed in the relavant Diagonal
     */
	static void _mainDiagonal(PosVar pos, PosVar dest, bool up, std::vector<PosVar>& moves);

	/**
 	* @brief inserts to moves the coordinates needed in the relavant Diagonal
 	*/
	static void _secondaryDiagonal(PosVar pos, PosVar dest, bool up, std::vector<PosVar>& moves);

	/**
	 * helper for queen and rook, returns a vertical or horizontal move. assume there is one
	 */
	static void _verOrHorMove(PosVar pos, PosVar dest, std::vector<PosVar>& moves);

	/**
	 * helper for queen and bishop, returns a diagonal move. assume there is one
	 */
	static void _diagonalMove(PosVar pos, PosVar dest, std::vector<PosVar>& moves);

};

#endif

