// ChessEngine.cpp
#include "ChessEngine.h"

/** @brief prints message with white text on red background */
void printRedMessage(std::string message);


//-------------------------------------ENGINE CTOR & DTOR-----------------------------------//

/** constructor for the engine. Initializes board with pieces*/
ChessEngine::ChessEngine(std::string whiteName, std::string blackName) : _board()
{
	_playerNames.push_back(whiteName);
	_playerNames.push_back(blackName);
	_whitePieces = _initPieces(WHITE);
	_blackPieces = _initPieces(BLACK);
	_putPieces(_whitePieces, WHITE_PAWNS_ROW, WHITE_SPECIAL_ROW); 
	_putPieces(_blackPieces, BLACK_PAWNS_ROW, BLACK_SPECIAL_ROW);
	_board.updateBoard();
	_isMate = _inCheck = _isCastling = _isMoveLegal = false;
	_currColor = WHITE;
	_kingPos.push_back(std::make_pair(KING_COL, FIRST_ROW)); // white king position
	_kingPos.push_back(std::make_pair(KING_COL, LAST_ROW)); // black king position
}

/** destructor, calls delete on allocations made for the pieces */
ChessEngine::~ChessEngine() noexcept
{
	for (int i = 0; i <= NUM_OF_PIECES; ++i)
	{
		delete _whitePieces[i];
		delete _blackPieces[i];
	}
}

//------------------------------------------RUN-----------------------------------------//

/** runs the game */
void ChessEngine::run()
{
	while (!_isMate)
	{
		while (!_isMoveLegal)
		{
			std::cout << _board;
			if (_inCheck)
			{
				printRedMessage(CHECK);
			}
			_isMoveLegal = _getMoveFromUser();
			_isMoveLegal = _isMoveLegal && _checkPieceExistenceAndColor(_start, _currColor);
			_isMoveLegal = _isMoveLegal && _makeMove();
			if (!_isMoveLegal)
			{
				printRedMessage(ILLEGAL_MOVE);
			}
		}
        _isMoveLegal = false;
		// Check  If enemy in check (or mate)
		_changePlayer();
		if ( (_inCheck = _isThreatened(_currColor, _kingPos[_currColor])) )
		{
			if ( (_isMate = _checkMate()) )
			{
				std::cout << _board;
				break;
			}

		}
	}
	_changePlayer();
	std::cout << _playerNames[_currColor] << " won!\n";
}

// -----------------------------MOVE CHECK FUNCTIONS-------------------------------------//

/** attempts to make user inputted move. If legal, updates board accordingly. */
bool ChessEngine::_makeMove()
{
	// if castling
	if (_isCastling) 
	{
		_isCastling = false;
		if ( !_checkCastling(_start, _dest) )
		{
			return false;
		}
	}
	// else normal move
	else
	{
		if ( !_checkMove(_start, _dest) )
		{
			return false;
		}
		_board.movePiece(_start, _dest);
	}
	_updateSpecialPieces(); // checks movements of rook and king, or pawn turning to queen
	_board.updateBoard();
	return true;
}

/** check if a certain move is legal by calling _checkPieceGetFromStartToDest, _checkLastPos and _checkCheck*/
bool ChessEngine::_checkMove(PosVar start, PosVar dest)
{
	if (_checkPieceGetFromStartToDest(start, dest, true) && _checkLastPos(dest) )
	{
		return _checkCheck(start, dest);
	}
	return false;
}
/** Checks if the king of _currColor is in check because of given move */
bool ChessEngine::_checkCheck(PosVar start, PosVar dest)
{
	_board.movePiece(start, dest);
	PosVar temp = _kingPos[_currColor];
	_updateKingPos(dest);
	// Check if we got ourselves into check. If we did, reverseMove();
	if (_isThreatened(_currColor, _kingPos[_currColor]) )
	{
		_kingPos[_currColor] = temp;
		_board.reverseMove();
		return false;
	}
	_kingPos[_currColor] = temp;
	_board.reverseMove();
	return true;
}

/** Check if the given dest (usually king of given color) is threatened by pieces of different color */
bool ChessEngine::_isThreatened(Color color, PosVar dest)
{
	std::vector<PosVar> piecePos;
	if (color == WHITE)
	{
		piecePos = _board.getPosIf(_getBlackPieces);
	}
	else
	{
		piecePos = _board.getPosIf(_getWhitePieces);
	}
	
	for (PosVar pos : piecePos)
	{
		if (_checkPieceGetFromStartToDest(pos, dest, false))
		{
			return true;
		}
	}
	return false;
}

/** Checks if there's a piece of given color at given position */
bool ChessEngine::_checkPieceExistenceAndColor(PosVar pos, Color color) const
{
	if (_board.getPiece(pos) == nullptr)
	{
		return false;
	}
	else if ( (_board.getPiece(pos))->getColor() != color)
	{
		return false;
	}
	return true;
}

/** check if piece at point start can move to dest. includes Pawn eat */
bool ChessEngine::_checkPieceGetFromStartToDest(PosVar start, PosVar dest, bool CheckPawnDiagonal) const
{
	if ( (_board.getPiece(start))->getType() == PAWN )
	{
		return _checkPawnMove(start, dest, CheckPawnDiagonal);
	}
	else
	{
		return _checkPieceGetFromStartToDestHelper(start, dest);
	}
}

/** check if piece at point start can move to dest. doesn't include Pawn eat */
bool ChessEngine::_checkPieceGetFromStartToDestHelper(PosVar start, PosVar dest) const
{
	std::vector<PosVar> moves = (_board.getPiece(start))->move(start, dest);
	if (moves.empty())
	{	
		return false;
	}
	
	return _board.isRangeEmpty(moves);
}

/** Checks that a move can end at last position - specifically if there's a piece
* there, that it's of a different color from _currColor */
bool ChessEngine::_checkLastPos(PosVar dest)
{
	// If there's a piece at _dest, check it's of different color
	if ((_board.getPiece(dest)) != nullptr)
	{
		return (_board.getPiece(dest))->getColor() != _currColor;
	}
	return true;
}

/** checks if the pawn at start can get to dest. Includes eating and vertical move */
bool ChessEngine::_checkPawnMove(PosVar start, PosVar dest, bool CheckPawnDiagonal) const
{
    const Pawn* pawnP = dynamic_cast<const Pawn*>(_board.getPiece(start));
    // If this is eating
    if (pawnP->isEatOption(start, dest))
    {
    	if (CheckPawnDiagonal)
    	{
	    	return _checkPieceExistenceAndColor(dest, static_cast<Color>((_currColor + 1) % 2));
    	}
        return true;
    }
    // vertical walk
    else
    {
    	if (_checkPieceGetFromStartToDestHelper(start, dest))
    	{
    		// make sure there are no pieces at dest
    		return (_board.getPiece(dest) == nullptr);
    	}
    }
    return false;
}

/** Check if we got the current color king into mate */
bool ChessEngine::_checkMate()
{	
	King tempKing {KING, WHITE};
	std::vector<std::pair<Piece*, PosVar>> OurPieces;
	// Do all possible moves to check if it's just a check or a real checkmate
	if (_currColor == WHITE)
	{
		OurPieces = _board.getPointersAndPosIf(_getWhitePieces);
	}
	else
	{
		OurPieces = _board.getPointersAndPosIf(_getBlackPieces);
	}
	for (unsigned i = 0; i < OurPieces.size(); i++)
	{
		std::vector<PosVar> possibleMoves = (OurPieces[i].first)->getAllMoves(OurPieces[i].second);
		for (PosVar move : possibleMoves)
		{
		    if (_board.inRange(move) && (_checkMove(OurPieces[i].second, move)) )
			{
				return false;
			}
		}
	}
	return true;
}

/** helper for castling, checks range is empty and points aren't in check. Moves pieces if legal */
bool ChessEngine::_checkCastlingHelper(PosVar kingPos, PosVar rookPos)
{
    // king-side castling
    if (rookPos.first > kingPos.first)
    {
        if ( (_board.getPiece(PosVar(kingPos.first + 1, kingPos.second)) == nullptr)
        	 && (_board.getPiece(PosVar(kingPos.first + 2, kingPos.second)) == nullptr) )
    	{
    		if ( !_isThreatened(_currColor, PosVar(kingPos.first + 1, kingPos.second)) )
    		{
				PosVar kingDest (kingPos.first + 2, kingPos.second);
				if (_checkCheck(kingPos, kingDest)) // check we don't end up in check
				{
					_board.movePiece(kingPos, kingDest);
                    _kingPos[_currColor] = kingDest;
					_board.movePiece(rookPos, PosVar(rookPos.first - 2 , rookPos.second));
					return true;
				}
    		}
    	}
    	return false;
    }
    // queen-side castling
    else
    {
        if ( (_board.getPiece(PosVar(kingPos.first - 1, kingPos.second)) == nullptr)
        	 && (_board.getPiece(PosVar(kingPos.first - 2, kingPos.second)) == nullptr) )
    	{
    		if ( !_isThreatened(_currColor, PosVar(kingPos.first - 1, kingPos.second)) )
    		{
				PosVar kingDest (kingPos.first - 2, kingPos.second);
				if (_checkCheck(kingPos, kingDest)) // check we don't end up in check
				{
					_board.movePiece(kingPos, kingDest);
					_board.movePiece(rookPos, PosVar(rookPos.first + 3 , rookPos.second));
					return true;
				}
    		}
    	}
    }
	return false;

}

/** checks if the move is correct castling. doing the move if true */
bool ChessEngine::_checkCastling(PosVar kingPos, PosVar rookPos)
{
    if (_inCheck)
    {
        return false;
    }
    if ( (_board.getPiece(kingPos) == nullptr) || (_board.getPiece(rookPos) == nullptr) ||
    	 (_board.getPiece(kingPos)->getType() != KING) || (_board.getPiece(rookPos)->getType() != ROOK))
	{
	 	return false;
	}

    King* king = dynamic_cast<King*>(_board.getPiece(kingPos));
    Rook* rook = dynamic_cast<Rook*>(_board.getPiece(rookPos));

    if ( king->getMoved() || rook->getMoved() )
    {
        return false;
    }
    return _checkCastlingHelper(kingPos, rookPos);
}

//------------------------------------GAME INIT FUNCTIONS--------------------------------------//

/** constructs new pieces */
std::vector<Piece*> ChessEngine::_initPieces(Color color)
{
    std::vector<Piece*> arrayOfPieces(NUM_OF_PIECES + 1);
	arrayOfPieces[PAWN] = new Pawn(PAWN, color);
	arrayOfPieces[ROOK] = new Rook(ROOK, color);
	arrayOfPieces[ROOK + 1] = new Rook(ROOK, color);
	arrayOfPieces[KNIGHT] = new Knight(KNIGHT, color);
	arrayOfPieces[BISHOP] = new Bishop(BISHOP, color);
	arrayOfPieces[QUEEN] = new Queen(QUEEN, color);
	arrayOfPieces[KING] = new King(KING, color);
    return arrayOfPieces;
}

/**  places pieces on board */
void ChessEngine::_putPieces(std::vector<Piece*>& arrayOfPieces, int pawnsRow, int specialRow)
{
	PosVar pos (FIRST_COL, pawnsRow);
	// Adding pawns
	for (; pos.first < FIRST_COL + NUM_OF_COLS; ++pos.first)
	{
		_board.addPiece(pos, arrayOfPieces[PAWN]);
	}
	// Adding special row
	pos = std::make_pair (FIRST_COL, specialRow);
	_board.addPiece(pos, arrayOfPieces[ROOK]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[KNIGHT]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[BISHOP]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[QUEEN]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[KING]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[BISHOP]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[KNIGHT]);
	pos.first++;
	_board.addPiece(pos, arrayOfPieces[ROOK + 1]);
}

//-------------------------------ENGINE I/O FUNCTIONS------------------------------------//

/** take move from user of the form <Column><Number><Column><Number> (or castling) for example "E1E2"
* and updates _start and _dest to hold move. Calls board.inRange */
bool ChessEngine::_getMoveFromUser()
{
	char input[MAX_INPUT_SIZE + 1]; // using c-string since Yoni recommended to use istream.getLine()
	
	std::cout << _playerNames[_currColor] << ": Please enter your move:\n";
	std::cin.getline(input, sizeof(input), '\n');
	if (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	_convertFromStringToPosVar(input);
	return ( _board.inRange(_start) && _board.inRange(_dest) );
}



/** convert user inputted move to two PosVar, updating _start and _dest */ 
void ChessEngine::_convertFromStringToPosVar(std::string input)
{
	if (input.compare(KING_SIDE_CASTLING) == 0)
	{
		if (_currColor == WHITE)
		{
			_start = PosVar(KING_COL, FIRST_ROW);
			_dest = PosVar(LAST_COL, FIRST_ROW);
		}
		else
		{
			_start = PosVar(KING_COL, LAST_ROW);
			_dest = PosVar(LAST_COL, LAST_ROW);
		}
		_isCastling = true;
		
	}
	else if (input.compare(QUEEN_SIDE_CASTLING) == 0)
	{
		if (_currColor == WHITE)
		{
			_start = PosVar(KING_COL, FIRST_ROW);
			_dest = PosVar(FIRST_COL, FIRST_ROW);
		}
		else
		{
			_start = PosVar(KING_COL, LAST_ROW);
			_dest = PosVar(FIRST_COL, LAST_ROW);
		}
		_isCastling = true;
	}
	// else, if normal move	
	else
	{
		_start = PosVar(input[0], input[1] - '0');
		_dest = PosVar(input[2], input[3] - '0');
	}
}

/** prints message in white letters over red background */
void printRedMessage(std::string message)
{
	std::cout << "\33[" + WHITE_TEXT + ";" + RED_BACK + "m" + message + "\33[0m" << std::endl;
}

//---------------------------ENGINE HELPER FUNCTIONS-------------------------------------//

/** Updates position of king of _currColor if needed */
void ChessEngine::_updateKingPos(PosVar dest)
{
	if (_board.getPiece(dest)->getType() == KING)
	{
		_kingPos[_currColor] = dest;
	}
}

/** If moved king or rook, update their getMoved flags. If Pawn reached last row, change it to Queen */
void ChessEngine::_updateSpecialPieces()
{
    if ( (_board.getPiece(_dest) != nullptr) && (_board.getPiece(_dest)->getType() == PAWN) )
    {
        if (_currColor == WHITE && _dest.second == LAST_ROW)
        {
            _board.removePiece(_dest);
            _board.addPiece(_dest, _whitePieces[QUEEN]);
        }
        else if (_currColor == BLACK && _dest.second == FIRST_ROW)
        {
            _board.removePiece(_dest);
            _board.addPiece(_dest, _blackPieces[QUEEN]);
        }
    }
    
	if ( (_board.getPiece(_dest) != nullptr) && (_board.getPiece(_dest)->getType() == KING) )
	{
		King* king = dynamic_cast<King*>(_board.getPiece(_dest));
		king->setMoved(true);
	}
	
	else if( (_board.getPiece(_dest) != nullptr) && (_board.getPiece(_dest)->getType() == ROOK) )
	{
		Rook* rook = dynamic_cast<Rook*>(_board.getPiece(_dest));
		rook->setMoved(true);
	}
}

/** unaryPredicate that gets a piece pointer and returns true if the piece is white*/
bool ChessEngine::_getWhitePieces(Piece* piecePtr)
{
	return (piecePtr)->getColor() == WHITE;
}

/** unaryPredicate that gets a piece pointer and returns true if the piece is black*/
bool ChessEngine::_getBlackPieces(Piece* piecePtr)
{
	return (piecePtr)->getColor() == BLACK;
}

/** change from Player A to player B, or vice versa*/
void ChessEngine::_changePlayer()
{
	_currColor = static_cast<Color> ((_currColor + 1) % 2); // change player 
}

