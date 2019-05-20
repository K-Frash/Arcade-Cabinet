#ifndef __PAWN_H__
#define __PAWN_H__
#include "colours.h"
#include "piece.h"

class Pawn: public Piece {
 public:
  Pawn(const Board &b, int file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'P': 'p') {}
  Pawn(const Board &b, char file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'P': 'p') {}
  Pawn(const Pawn &p, Board &b): Piece(b, p.file, p.rank, p.colour, p.repn) {}
  std::vector<std::pair<int, int> > getMoves() const;

  virtual Pawn *clone(Board *b) const;
};

#endif
