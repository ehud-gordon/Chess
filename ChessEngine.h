//ChessEngine.h
//--------------------------------------INCLUDES--------------------------------------------//
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Board.h"
#include "Constants.h"
#include <limits>
#include <cstring>
#include <string>
#include <cctype>

//-----------------------------------CONSTANTS--------------------------------------------//

const static int WHITE_PAWNS_ROW = FIRST_ROW + 1;
const static int WHITE_SPECIAL_ROW = FIRST_ROW;
const static int BLACK_SPECIAL_ROW = LAST_ROW;
const static int BLACK_PAWNS_ROW = BLACK_SPECIAL_ROW - 1;
const static std::string KING_SIDE_CASTLING = "o-o";
const static std::string QUEEN_SIDE_CASTLING = "o-o-o";
const static int MAX_INPUT_SIZE = 5;

const std::string ILLEGAL_MOVE = "illegal move";
const std::string CHECK = "Check!";

const static int NUM_OF_PIECES = 6;
const static int MOVE_SIZE = 4; /** size of input of a move */
const static char KING_COL = 'E';

//-----------------------------------CLASS DECLARATION-----------------------------------------//

/**
* A class representing an Engine that runs a chess game, with getting input, checking rules
* and updating user of status
*/
class ChessEngine
{
public:
	/**
	* the main function of the engine, gets user input and check its legality, asks for input
	* until user enters a legal move. If the move caused a check prints a notification.
	* gets users moves until a checkmate happens, and then prints winner
	*/ 
	void run();

//-------------------------------------ENGINE CTOR & DTOR-----------------------------------//

	/**
	* constructor for the engine. Initializes board with pieces.
	* @param whiteName name of the white player
	* @param blackName name of the black player
	*/
	ChessEngine(std::string whiteName, std::string blackName);
	
	/** deletes all the allocations made for the pieces */
	~ChessEngine() noexcept;
		
private:

//-----------------------------------ENGINE PRIVATE DATA-------------------------------//

	Board _board;
	std::vector<std::string> _playerNames;
	std::vector<Piece*> _whitePieces, _blackPieces;
	Color _currColor;
	bool _isMate, _inCheck, _isMoveLegal, _isCastling;
	PosVar _start, _dest;
	std::vector<PosVar> _kingPos; /** holds the white and black kings' positions, respectively */

    
// -----------------------------MOVE CHECK FUNCTIONS-------------------------------------//

	/** 
	* attemps to make a move
	* @return true if the move is legal, false otherwise
	*/
	bool _makeMove();

	/**  
	* @param start location of piece to move
	* @param dest destination of piece
	* @return true if can move piece from start to dest, false otherwise
	*/
	bool _checkMove(PosVar start, PosVar dest);
	
	/** check if a given move from start to dest will put king of _currColor in check
	* @param 
	* @param
	* @return
	*/
	bool _checkCheck(PosVar start, PosVar dest);
	
    /** checks Pawn movement 
    * @param start position of a pawn
    * @param dest destination to move pawn to
    * @return true if pawn can make that move, false otherwise
    */
    bool _checkPawnMove(PosVar start, PosVar dest, bool CheckPawnDiagonal) const;
	
	/**
	* @param pos location to check existence of piece
	* @param color color the piece need to have
	* @param CheckPawnDiagonal a boolean whether this move indicatses a move of pawn
	* into unknown cell (as in the case of _checkMove) or a move into a cell
	* containing a known piece (As in the case of _isThreatened)
	* @return true if there's a piece of given color at the given position
	*/ 
	bool _checkPieceExistenceAndColor(PosVar pos, Color color) const;
	
	/** 
	* checks if we can move a piece from start to dest, including pawn eat
	* @param start location of a cell containing a piece
	* @param dest location of where we want to move that piece
	* @return true if the piece at start can get to dest
	*/
	bool _checkPieceGetFromStartToDest(PosVar start, PosVar dest, bool CheckPawnDiagona) const;
	
	/** helper function to _checkPieceGetFromStartToDest, doesn't include pawn eat*/
	bool _checkPieceGetFromStartToDestHelper(PosVar start, PosVar dest) const;
	
	/** Checks that the last position doesn't contain a piece of the current color*/
	bool _checkLastPos(PosVar dest);
	
	/** check if the dest position is threatened by pieces of the color different from the given one*/
	bool _isThreatened(Color color, PosVar dest);
	
	/** check if we got the enemy king into mate */
	bool _checkMate();
	
	/** checks if castling is legal, and moves pieces if it is */
    bool _checkCastling(PosVar kingPos, PosVar rookPos);

	/** checks castling range is empty and the midpoint isn't in check and moves pieces if legal */
    bool _checkCastlingHelper(PosVar kingPos, PosVar rookPos);

// --------------------------------GAME INIT FUNCTIONS--------------------------------------//

	/**
	* Constructs new pieces of given color and places them in given container
	* @arrayOfPieces a container to be inserted with the new pieces
	* @color the color with which to create the pieces
	*/
	std::vector<Piece*> _initPieces(Color color);
	
	/**
	* composes the board with the game pieces at the right places
	* @param arrayOfPieces set of pieces to add to the board, composed of pawns and special pieces
	* @param pawnsRow row to put the pieces in
	* @param specialRow row to put special pieces in
	*/
	void _putPieces(std::vector<Piece*>& arrayOfPieces, int pawnsRow, int specialRow);	

// -----------------------------ENGINE I/O FUNCTIONS-----------------------------------------//

	/** converts user inputted move into a start move and destination move
	* @param input a string holding the user inputted move
	*/
	void _convertFromStringToPosVar(std::string input);
	
	/**
	* take move from user of the form <Column><Number><Column><Number> (or castling) for example "E1E2"
	* f legal and in range, updates _start and _dest to hold move
	* @return true if the user inputted a move in a legal format which is in board range, false otherwise
	*/
	bool _getMoveFromUser();

// ------------------------------ENGINE HELPER FUNCTIONS----------------------------------//

	/** Updates the king position if needed */
	void _updateKingPos(PosVar dest);
	
	/** after move has been done, does special checks - specifically, if Pawn has reached last row,
	* or if a king or rook has been moved, and if so - updates their state. */
	void _updateSpecialPieces();
	
	/** changes player from A to B or vice versa */
	void _changePlayer();
	
	/** get all pieces of White Color*/
	static bool _getWhitePieces(Piece* piecePtr);
	
	/** get all pieces of Black Color*/
	static bool _getBlackPieces(Piece* piecePtr);
};

