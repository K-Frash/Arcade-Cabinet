#include "pawn.h"
#include "board.h"
using namespace std;

vector<pair<int, int> > Pawn::getMoves() const {
  vector<pair<int, int> > v;
  int incr = colour == White ? 1 : -1;
  int firstRank = colour == White ? 1 : 6;
  int thirdRank = colour == White ? 3 : 4;

  if (!theBoard.pieceAt(file, rank + incr)) {
    v.push_back(make_pair(file, rank + incr));
    if (rank == firstRank && !theBoard.pieceAt(file, thirdRank)) {
      v.push_back(make_pair(file, thirdRank));
    }
  }
  if (file > 0) {
    const Piece *p = theBoard.pieceAt(file - 1, rank + incr);
    if (p && p->getColour() != colour)
      v.push_back(make_pair(file - 1, rank + incr));
  }
  if (file < 7) {
    const Piece *p = theBoard.pieceAt(file + 1, rank + incr);
    if (p && p->getColour() != colour)
      v.push_back(make_pair(file + 1, rank + incr));
  }

  // Need to check for en passant
  const Pawn *p = theBoard.enPassant;
  if (p && p->getRank() == rank &&
         (p->getFile() == file-1 || p->getFile() == file+1)) {
    v.push_back(make_pair(p->getFile(), rank + incr));
  }
  return v;
}

Pawn *Pawn::clone(Board *b) const { return new Pawn(*this, *b); }
