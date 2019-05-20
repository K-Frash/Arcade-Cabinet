#include <iostream>
#include "king.h"
#include "rook.h"
#include "board.h"
using namespace std;

vector<pair<int, int> > King::getMoves() const {
  vector<pair<int, int> > v;
  if (file > 0 && rank > 0) {
    const Piece *p = theBoard.pieceAt(file - 1, rank - 1);
    if (!p || p->getColour() != colour)
       v.push_back(make_pair(file - 1, rank - 1));  
  }
  if (file > 0 && rank < 7) {
    const Piece *p = theBoard.pieceAt(file - 1, rank + 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file - 1, rank + 1));  
  }
  if (file < 7 && rank > 0) {
    const Piece *p = theBoard.pieceAt(file + 1, rank - 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 1, rank - 1));  
  }
  if (file < 7 && rank < 7) {
    const Piece *p = theBoard.pieceAt(file + 1, rank + 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 1, rank + 1));  
  }
  if (file > 0) {
    const Piece *p = theBoard.pieceAt(file - 1, rank);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file - 1, rank));  
  }
  if (file < 7) {
    const Piece *p = theBoard.pieceAt(file + 1, rank);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 1, rank));  
  }
  if (rank > 0) {
    const Piece *p = theBoard.pieceAt(file, rank - 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file, rank - 1));  
  }
  if (rank < 7) {
    const Piece *p = theBoard.pieceAt(file, rank + 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file, rank + 1));  
  }

  // Check for castling
  if (!hasMoved) {
    // Kingside
    const Piece *b = theBoard.pieceAt(file + 1, rank);
    const Piece *n = theBoard.pieceAt(file + 2, rank);
    const Piece *r = theBoard.pieceAt(file + 3, rank);
    if (!b && !n && r) {
      const Rook *rk = dynamic_cast<const Rook*>(r);
      if (rk && !rk->moved()) {
        // Need no check on the intermediate square
        Board b = theBoard;
        if (!b.check(colour)) {
          if (!b.wouldCheck(make_pair(file, rank), make_pair(file + 1, rank))) 
            v.push_back(make_pair(file + 2, rank));
        }
      }
    }

    // Queenside
    const Piece *q = theBoard.pieceAt(file - 1, rank);
    b = theBoard.pieceAt(file - 2, rank);
    n = theBoard.pieceAt(file - 3, rank);
    r = theBoard.pieceAt(file - 4, rank);
    if (!q && !b && !n && r) {
      const Rook *rk = dynamic_cast<const Rook*>(r);
      if (rk && !rk->moved()) {
        // Need no check on the intermediate square
        Board b = theBoard;
        if (!b.check(colour)) {
          if (!b.wouldCheck(make_pair(file, rank), make_pair(file - 1, rank))) 
            v.push_back(make_pair(file - 2, rank));
        }
      }
    }
  }
  return v;
}

King *King::clone(Board *b) const { return new King(*this, *b); }

void King::move(int newFile, int newRank) {
  Piece::move(newFile, newRank);
  hasMoved = true;
}
