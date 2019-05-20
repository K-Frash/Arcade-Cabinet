#include "queen.h"
#include "board.h"
using namespace std;

vector<pair<int, int> > Queen::getMoves() const {
  vector<pair<int, int> > v;
  for (int i = 1; file + i <= 7 && rank + i <= 7; ++i) {
    const Piece *p = theBoard.pieceAt(file + i, rank + i);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file + i, rank + i));
    if (p) break;
  }

  for (int i = 1; file - i >= 0 && rank + i <= 7; ++i) {
    const Piece *p = theBoard.pieceAt(file - i, rank + i);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file - i, rank + i));
    if (p) break;
  }

  for (int i = 1; file + i <= 7 && rank - i >= 0; ++i) {
    const Piece *p = theBoard.pieceAt(file + i, rank - i);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file + i, rank - i));
    if (p) break;
  }

  for (int i = 1; file - i >= 0 && rank - i >= 0; ++i) {
    const Piece *p = theBoard.pieceAt(file - i, rank - i);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file - i, rank - i));
    if (p) break;
  }

  for (int i = 1; file - i >= 0; ++i) {
    const Piece *p = theBoard.pieceAt(file - i, rank);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file - i, rank));
    if (p) break;
  }

  for (int i = 1; file + i <= 7; ++i) {
    const Piece *p = theBoard.pieceAt(file + i, rank);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file + i, rank));
    if (p) break;
  }

  for (int i = 1; rank - i >= 0; ++i) {
    const Piece *p = theBoard.pieceAt(file, rank - i);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file, rank - i));
    if (p) break;
  }

  for (int i = 1; rank + i <= 7; ++i) {
    const Piece *p = theBoard.pieceAt(file, rank + i);
    if (p && p->getColour() == colour) break;
    v.push_back(make_pair(file, rank + i));
    if (p) break;
  }
  return v;
}

Queen *Queen::clone(Board *b) const { return new Queen(*this, *b); }
