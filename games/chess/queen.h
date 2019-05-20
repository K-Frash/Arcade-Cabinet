#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "colours.h"
#include "piece.h"

class Queen: public Piece {
 public:
  Queen(const Board &b, int file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'Q': 'q') {}
  Queen(const Board &b, char file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'Q': 'q') {}
  Queen(const Queen &q, Board &b): Piece(b, q.file, q.rank, q.colour, q.repn) {}
  std::vector<std::pair<int, int> > getMoves() const;

  virtual Queen *clone(Board *b) const;
};

#endif
