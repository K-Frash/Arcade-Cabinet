#include <iostream>
#include "piece.h"
#include "computer1.h"
#include "posn.h"
#include <utility>
#include <cstdlib>
using namespace std;

pair<Posn,Posn> Computer1::getMove() {
  vector<pair<Posn,Posn> > moves = myLegalMoves();
  int choice = rand() % moves.size();
  pair<Posn,Posn> result = moves[choice];
  cout << result.first << "-" << result.second << endl;
  result.first.first += 'a';
  result.first.second += 1;
  result.second.first += 'a';
  result.second.second += 1;
  return result;
}

char Computer1::promote() { return 'Q'; }
