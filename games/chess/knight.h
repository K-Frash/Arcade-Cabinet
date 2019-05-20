#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "colours.h"
#include "piece.h"

class Knight: public Piece {
 public:
  Knight(const Board &b, int file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'N': 'n') {}
  Knight(const Board &b, char file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'N': 'n') {}
  Knight(const Knight &k, Board &b): Piece(b, k.file, k.rank, k.colour, k.repn) {}
  std::vector<std::pair<int, int> > getMoves() const;

  virtual Knight *clone(Board *b) const;
};

#endif
