#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <utility>
#include <vector>
#include "posn.h"
#include "colours.h"
#include "king.h"
#include "pawn.h"
#include "computer.h"
class Piece;

class Promote{};
class Checkmate{};
class Stalemate{};

class Board {
  Piece *theBoard[8][8];
  std::pair<int,int> whiteKing;
  std::pair<int,int> blackKing;
  Colour turn;
  Pawn *enPassant;
  int promoteFile, promoteRank;

  mutable std::vector<std::pair<Posn,Posn> > legalMoves;

  void flipTurn() { turn = turn == White ? Black : White; }

  // Computes legal moves, without regard for whether they would put the king
  // in check.
  void baseLegalMoves() const; 

  void computeLegalMoves() const;


  // Carry out move without checking for validity.
  // Returns true if a piece was removed from the board
  bool baseMove(int fileFrom, int rankFrom, int fileTo, int rankTo);

  // Checks to see if the game is checkmated or stalemated.  Throws an
  // exception if it is.
  void checkForMates() const;
 public:
  Board();
  Board(const Board &other);
  ~Board();

  void clear(); // Clears the board
  void init();  // Sets up initial game configuration

  const Piece *pieceAt(int file, int rank) const;
  Colour getTurn() const { return turn; }
  void setTurn(Colour c) { turn = c; }

  bool move(int fileFrom, int rankFrom, int fileTo, int rankTo);
  bool move(char fileFrom, int rankFrom, char fileTo, int rankTo);

  void promote(char c);; // Promote most recently-moved pawn to Q, B, N, or R

  // Returns true if a move would put the king in check.
  bool wouldCheck(Posn from, Posn to) const;
  bool check(Colour c) const; // Returns true if c's King is in check

  bool addPiece(char pc, int file, int rank);
  void removePiece(int file, int rank);
  bool verify() const;

  friend std::ostream &operator<<(std::ostream &out, const Board &b);
  friend std::vector<std::pair<int,int> > King::getMoves() const;
  friend std::vector<std::pair<int,int> > Pawn::getMoves() const;
  friend std::vector<std::pair<Posn,Posn> > Computer::myLegalMoves() const;
};

#endif
