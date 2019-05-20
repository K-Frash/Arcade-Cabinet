#include <iostream>
#include <utility>
#include "posn.h"
#include "human.h"
using namespace std;

Human::Human(istream &in):in(in) {}
Human::~Human() {}

pair<Posn,Posn> Human::getMove() {
  char f1, f2;
  int r1, r2;

  if (!(in >> f1 >> r1 >> f2 >> r2)) setFail();

  return make_pair(make_pair(f1,r1), make_pair(f2,r2));
}

char Human::promote() {
  char result;
  while (in >> result) {
    if (result == 'Q' || result == 'q' || result == 'B' || result == 'b' ||
       result == 'N' || result == 'n' || result == 'R' || result == 'r') break;
  }
  return result;
}
