#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <utility>
#include <vector>
#include "colours.h"
class Board;

class Piece {
 protected:
  int rank, file;
  const Colour colour;
  const Board &theBoard;
  const char repn;
 public:
  Piece (const Board &b, int f, int r, Colour c, char repn): rank(r), file(f),
      colour(c), theBoard(b), repn(repn) {}
  Piece (const Board &b, char f, int r, Colour c, char repn): rank(r),
      file(f - 'a'), colour(c), theBoard(b), repn(repn) {}
  Piece (const Piece &p, const Board &b): rank(p.rank), file(p.file),
      colour(p.colour), theBoard(b), repn(p.repn) {}
  virtual ~Piece() {}
  int getRank() const { return rank; }
  int getFile() const { return file; }
  Colour getColour() const { return colour; }
  virtual std::vector<std::pair<int, int> > getMoves() const = 0;

  virtual Piece *clone(Board *b) const = 0;
  const char getRepn() const { return repn; }

  virtual void move(int newFile, int newRank);
};

std::ostream &operator<<(std::ostream &out, std::pair<int, int> posn);

std::ostream& printLegalMoves(std::ostream &out, std::pair<int, int> posn,
  std::vector<std::pair<int, int> > moves);
#endif
