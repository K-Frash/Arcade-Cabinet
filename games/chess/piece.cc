#include <iostream>
#include <utility>
#include <vector>
#include "piece.h"
using namespace std;

void Piece::move(int newFile, int newRank) {
  file = newFile;
  rank = newRank;
}

ostream &operator<<(ostream &out, pair<int, int> posn) {
  return out << static_cast<char>(posn.first + 'a') << posn.second + 1;
}

ostream& printLegalMoves(ostream &out, pair<int,int> posn, vector<pair<int,int> > moves) {
  for (vector<pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it) {
    out << posn << '-' << *it << ' ';
  }
  return out;
}

