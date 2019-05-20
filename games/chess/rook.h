#ifndef __ROOK_H__
#define __ROOK_H__
#include "colours.h"
#include "piece.h"

class Rook: public Piece {
 bool hasMoved;
 public:
  Rook(const Board &b, int file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'R': 'r'), hasMoved(false) {}
  Rook(const Board &b, char file, int rank, Colour c):
    Piece(b, file, rank, c, c == White? 'R': 'r'), hasMoved(false) {}
  Rook(const Rook &r, Board &b): Piece(b, r.file, r.rank, r.colour, r.repn), hasMoved(r.hasMoved) {}
  std::vector<std::pair<int, int> > getMoves() const;

  virtual Rook *clone(Board *b) const;
  void move(int newFile, int newRank);
  bool moved() const { return hasMoved; }
};

#endif
