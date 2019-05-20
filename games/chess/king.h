#ifndef __KING_H__
#define __KING_H__
#include "colours.h"
#include "piece.h"

class King: public Piece {
  bool hasMoved;
 public:
  King(const Board &b, int file, int rank, Colour c):
     Piece(b, file, rank, c, c == White? 'K': 'k'), hasMoved(false) {}
  King(const Board &b, char file, int rank, Colour c):
     Piece(b, file, rank, c, c == White? 'K': 'k'), hasMoved(false) {}
  King(const King &k, Board &b): Piece(b, k.file, k.rank, k.colour, k.repn), hasMoved(k.hasMoved) {}
  std::vector<std::pair<int, int> > getMoves() const;

  virtual King *clone(Board *b) const;
  void move(int newFile, int newRank);
};

#endif
