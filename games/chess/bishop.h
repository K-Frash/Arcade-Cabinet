#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "colours.h"
#include "piece.h"

class Bishop: public Piece {
 public:
  Bishop(const Board &b, int file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'B': 'b') {}
  Bishop(const Board &b, char file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'B': 'b') {}
  Bishop(const Bishop &bp, Board &b): Piece(b, bp.file, bp.rank, bp.colour, bp.repn) {}
  std::vector<std::pair<int, int> > getMoves() const;

  virtual Bishop *clone(Board *b) const;
};

#endif
