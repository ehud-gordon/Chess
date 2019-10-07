.PHONY: all clean tar test valdbg

CC = g++
CCFLAGS = -Wall -Wvla -Wextra -g -DNDEBUG -std=c++17
LC_F = --leak-check=full
SPL_Y = --show-possibly-lost=yes
SR_Y = --show-reachable=yes
UVE_Y = --undef-value-errors=yes
TR_Y = --track-origins=yes

all: chess

chess: Piece.o Board.o ChessEngine.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o chess.cpp
	$(CC) $(CCFLAGS) -I. -L. chess.cpp ChessEngine.o Board.o Piece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o -o chess
	
Piece.o:
	$(CC) $(CCFLAGS) -I. -c Piece.cpp
Board.o: Board.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c Board.cpp
ChessEngine.o: ChessEngine.cpp Piece.o Board.o
	$(CC) $(CCFLAGS) -I. -c ChessEngine.cpp
Pawn.o: Pawn.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c Pawn.cpp
Rook.o: Rook.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c Rook.cpp
Knight.o: Knight.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c Knight.cpp
Bishop.o: Bishop.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c Bishop.cpp
Queen.o: Queen.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c Queen.cpp
King.o: King.cpp Piece.o
	$(CC) $(CCFLAGS) -I. -c King.cpp

clean:
	rm -f chess ChessEngine.o Board.o Piece.o King.o Queen.o Bishop.o Knight.o Rook.o Pawn.o 

tar:
	tar -cvf ex2.tar chess.cpp ChessEngine.h ChessEngine.cpp Board.cpp Board.h Piece.cpp Piece.h \
	Pawn.h Pawn.cpp Rook.h Rook.cpp Knight.cpp Knight.h Bishop.h Bishop.cpp Queen.cpp Queen.h \
	King.cpp King.h Constants.h README Makefile
	
test: chess
	./chess
	
valdbg: chess
	valgrind $(LC_F) $(SPL_Y) $(SR_Y) $(UVE_Y) $(TR_Y) chess
	

