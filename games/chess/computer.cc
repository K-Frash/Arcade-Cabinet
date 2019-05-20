#include <vector>
#include "posn.h"
#include "computer.h"
#include "board.h"
using namespace std;

vector<Move> Computer::myLegalMoves() const { return b.legalMoves; }
