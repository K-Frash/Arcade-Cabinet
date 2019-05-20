#include "knight.h"
#include "board.h"
using namespace std;

vector<pair<int, int> > Knight::getMoves() const {
  vector<pair<int, int> > v;
  if (file > 1 && rank > 0) {
    const Piece *p = theBoard.pieceAt(file - 2, rank - 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file - 2, rank - 1));  
  }
  if (file > 0 && rank > 1) {
    const Piece *p = theBoard.pieceAt(file - 1, rank - 2);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file - 1, rank - 2));  
  }
  if (file < 7 && rank > 1) {
    const Piece *p = theBoard.pieceAt(file + 1, rank - 2);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 1, rank - 2));  
  }
  if (file < 6 && rank > 0) {
    const Piece *p = theBoard.pieceAt(file + 2, rank - 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 2, rank - 1));  
  }
  if (file > 1 && rank < 7) {
    const Piece *p = theBoard.pieceAt(file - 2, rank + 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file - 2, rank + 1));
  }
  if (file > 0 && rank < 6) {
    const Piece *p = theBoard.pieceAt(file - 1, rank + 2);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file - 1, rank + 2));
  }
  if (file < 7 && rank < 6) {
    const Piece *p = theBoard.pieceAt(file + 1, rank + 2);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 1, rank + 2));  
  }
  if (file < 6 && rank < 7) {
    const Piece *p = theBoard.pieceAt(file + 2, rank + 1);
    if (!p || p->getColour() != colour)
      v.push_back(make_pair(file + 2, rank + 1));  
  }
  return v;
}

Knight *Knight::clone(Board *b) const { return new Knight(*this, *b); }
