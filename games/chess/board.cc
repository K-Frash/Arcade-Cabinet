#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "colours.h"
#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
using namespace std;

Board::Board(): enPassant(0), promoteFile(-1), promoteRank(-1) {
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      theBoard[i][j] = 0;
  turn = White;
}

Board::Board(const Board &other): whiteKing(other.whiteKing),
        blackKing(other.blackKing), enPassant(other.enPassant),
        promoteFile(other.promoteFile), promoteRank(other.promoteRank) {
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      if (other.theBoard[i][j])
        theBoard[i][j] = other.theBoard[i][j]->clone(this);
      else
        theBoard[i][j] = 0;
  turn = other.turn;
}

Board::~Board() {
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      delete theBoard[i][j];
}

void Board::clear() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      delete theBoard[i][j];
      theBoard[i][j] = 0;
    }
  }
}

void Board::init() {
  clear();

  for (int i = 0; i < 8; ++i) {
    theBoard[i][1] = new Pawn(*this, i, 1, White);
    theBoard[i][6] = new Pawn(*this, i, 6, Black);
  }

  theBoard[0][0] = new Rook(*this, 0, 0, White);
  theBoard[1][0] = new Knight(*this, 1, 0, White);
  theBoard[2][0] = new Bishop(*this, 2, 0, White);
  theBoard[3][0] = new Queen(*this, 3, 0, White);
  theBoard[4][0] = new King(*this, 4, 0, White);
  theBoard[5][0] = new Bishop(*this, 5, 0, White);
  theBoard[6][0] = new Knight(*this, 6, 0, White);
  theBoard[7][0] = new Rook(*this, 7, 0, White);

  theBoard[0][7] = new Rook(*this, 0, 7, Black);
  theBoard[1][7] = new Knight(*this, 1, 7, Black);
  theBoard[2][7] = new Bishop(*this, 2, 7, Black);
  theBoard[3][7] = new Queen(*this, 3, 7, Black);
  theBoard[4][7] = new King(*this, 4, 7, Black);
  theBoard[5][7] = new Bishop(*this, 5, 7, Black);
  theBoard[6][7] = new Knight(*this, 6, 7, Black);
  theBoard[7][7] = new Rook(*this, 7, 7, Black);

  whiteKing = make_pair('e' - 'a', 1 - 1);
  blackKing = make_pair('e' - 'a', 8 - 1);
  turn = White;
  computeLegalMoves();
}

bool Board::wouldCheck(Posn from, Posn to) const {
  // Create temporary board as copy of *this, execute move, see if King is
  // in check.
  Board temp = *this;
  temp.baseMove(from.first, from.second, to.first, to.second);
  temp.flipTurn();
  temp.baseLegalMoves();
  temp.flipTurn();

  if (temp.check(temp.getTurn())) return true;

  return false;
}

const Piece *Board::pieceAt(int file, int rank) const {
  return theBoard[file][rank];
}

bool Board::baseMove(int fileFrom, int rankFrom, int fileTo, int rankTo) {
  if (whiteKing.first == fileFrom && whiteKing.second == rankFrom) {
    whiteKing = make_pair(fileTo, rankTo);
  }
  else if (blackKing.first == fileFrom && blackKing.second == rankFrom) {
    blackKing = make_pair(fileTo, rankTo);
  }

  bool retVal = theBoard[fileTo][rankTo];

  delete theBoard[fileTo][rankTo];
  theBoard[fileTo][rankTo] = theBoard[fileFrom][rankFrom];
  theBoard[fileFrom][rankFrom] = 0;
  theBoard[fileTo][rankTo]->move(fileTo, rankTo);

  return retVal;
}

bool Board::move(int fileFrom, int rankFrom, int fileTo, int rankTo) {
  // Check if the move is legal
  bool legal = false;

  for(vector<Move>::iterator it = legalMoves.begin(); it != legalMoves.end(); ++it) {
    if (it->first.first == fileFrom && it->first.second == rankFrom
        && it->second.first == fileTo && it->second.second == rankTo) {
      legal = true;
      break;
    }
  }

  if (!legal) return false;

  // Carry out the move
  bool captured = baseMove(fileFrom, rankFrom, fileTo, rankTo);

  // Handle castling
  if (dynamic_cast<King*>(theBoard[fileTo][rankTo])) {
    if (fileTo - fileFrom == 2) {
      baseMove(7,rankFrom,5,rankFrom); // Move the h1 or h8 rook
    }
    else if (fileTo - fileFrom == -2) {
      baseMove(0,rankFrom,3,rankFrom); // Move the a1 or a8 rook
    }
  }

  // Handle en passant
  if (Pawn *p = dynamic_cast<Pawn*>(theBoard[fileTo][rankTo])) {
    // If the pawn is executing en passant, capture the other pawn.
    if (fileFrom != fileTo) {  // If the pawn was capturing
      if (!captured) { // but no piece was removed
        delete theBoard[fileTo][rankFrom];
        theBoard[fileTo][rankFrom] = 0;
      }
      enPassant = 0;
    }

    // If the pawn moves two squares forward, it is vulnerable to en passant.
    else if (rankFrom - rankTo == 2 || rankFrom - rankTo == -2) {
      enPassant = p;
    }
    else {
      enPassant = 0;
    }

    // Handle pawn promotion
    if (rankTo == 0 || rankTo == 7) {
      promoteFile = fileTo;
      promoteRank = rankTo;
      throw Promote();
    }
  }
  else {
    enPassant = 0;
  }


  // Switch turns and compute legal moves
  flipTurn();
  computeLegalMoves();
  checkForMates();
  return true;
}

bool Board::move(char fileFrom, int rankFrom, char fileTo, int rankTo) {
  return move(fileFrom - 'a', rankFrom - 1, fileTo - 'a', rankTo - 1);
}

bool Board::check(Colour c) const {
  Posn king = c == White ? whiteKing : blackKing;

  for (int rank = 7; rank >= 0; --rank) {
    for (int file = 0; file < 8; ++file) {
      const Piece *p = theBoard[file][rank];
      if (p && p->getColour() != c) {
        // Handle the opposing king separately.  Prevents an
        // infinite recursion, because the opposing king's moves
        // may include castling, for which the opposing king must
        // not be in check, which implies checking the current
        // colour's legal moves, including the current king's ...
        if (!dynamic_cast<const King*>(p)) {
          vector<Posn> v = p->getMoves();
          for (vector<Posn>::iterator it = v.begin(); it != v.end(); ++it) {
            if (*it == king) return true;
          }
        }
        // You're in check by the king if you're adjacent to it
        // (which can't happen, but could if you're considering
        // possible moves to get out of check).
        else {
          if (abs(file - king.first) <= 1 && abs(rank - king.second) <= 1) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

void Board::promote(char c) {
  Colour colour = promoteRank == 0 ? Black : White;
  delete theBoard[promoteFile][promoteRank];

  if (c == 'Q' || c == 'q')
    theBoard[promoteFile][promoteRank] = new Queen(*this, promoteFile, promoteRank, colour);
  else if (c == 'B' || c == 'b')
    theBoard[promoteFile][promoteRank] = new Bishop(*this, promoteFile, promoteRank, colour);
  else if (c == 'N' || c == 'n')
    theBoard[promoteFile][promoteRank] = new Knight(*this, promoteFile, promoteRank, colour);
  else if (c == 'R' || c == 'r')
    theBoard[promoteFile][promoteRank] = new Rook(*this, promoteFile, promoteRank, colour);

  promoteFile = promoteRank = -1;
  flipTurn();
  computeLegalMoves();
  checkForMates();
}

void Board::baseLegalMoves() const {
  legalMoves.erase(legalMoves.begin(), legalMoves.end());

  for (int rank = 7; rank >= 0; --rank) {
    for (int file = 0; file < 8; ++file) {
      const Piece *p = theBoard[file][rank];
      if (p && p->getColour() == turn) {
        Posn pn = make_pair(file,rank);
        vector<Posn> moves = p->getMoves();
        for (vector<Posn>::iterator it = moves.begin(); it != moves.end(); ++it) {
          legalMoves.push_back(make_pair(pn, *it));
        }
      }
    }
  }
}

void Board::computeLegalMoves() const {
  baseLegalMoves();

  for (vector<Move>::iterator it = legalMoves.begin(); it != legalMoves.end();) {
    if (wouldCheck(it->first, it->second)) {
      it = legalMoves.erase(it);
    }
    else ++it;
  }
}

void Board::checkForMates() const {
  if (legalMoves.size() == 0) {
    if (check(turn)) throw Checkmate();
    else throw Stalemate();
  }
}

bool Board::addPiece(char pc, int file, int rank) {
  switch(pc) {
    case 'K':
      whiteKing = make_pair(file, rank);
      delete theBoard[file][rank];
      theBoard[file][rank] = new King(*this, file, rank, White);
      return true;
    case 'k':
      blackKing = make_pair(file, rank);
      delete theBoard[file][rank];
      theBoard[file][rank] = new King(*this, file, rank, Black);
      return true;
    case 'Q':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Queen(*this, file, rank, White);
      return true;
    case 'q':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Queen(*this, file, rank, Black);
      return true;
    case 'B':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Bishop(*this, file, rank, White);
      return true;
    case 'b':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Bishop(*this, file, rank, Black);
      return true;
    case 'N':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Knight(*this, file, rank, White);
      return true;
    case 'n':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Knight(*this, file, rank, Black);
      return true;
    case 'R':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Rook(*this, file, rank, White);
      return true;
    case 'r':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Rook(*this, file, rank, Black);
      return true;
    case 'P':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Pawn(*this, file, rank, White);
      return true;
    case 'p':
      delete theBoard[file][rank];
      theBoard[file][rank] = new Pawn(*this, file, rank, Black);
      return true;
  }
  return false;
}

void Board::removePiece(int file, int rank) {
  delete theBoard[file][rank];
  theBoard[file][rank] = 0;
}

bool Board::verify() const {
  // Need exactly one king of each colour.
  // Pawns must be on ranks 2-7
  int wKingCount = 0, bKingCount = 0;

  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (theBoard[i][j]) {
        if (King *k = dynamic_cast<King*>(theBoard[i][j])) {
          if (k->getColour() == White) ++wKingCount;
          if (k->getColour() == Black) ++bKingCount;
        }

        Pawn *p = dynamic_cast<Pawn*>(theBoard[i][j]);
        if (p && (p->getRank() == 0 || p->getRank() == 7)) {
          return false;
        }
      }
    }
  }
  if (wKingCount != 1 || bKingCount != 1) return false;

  computeLegalMoves();
  return true;
}

ostream &operator<<(ostream &out, const Board &b) {
  for (int rank = 7; rank >= 0; --rank) {
    out << rank + 1 << " ";
    for (int file = 0; file < 8; ++file) {
      if (b.theBoard[file][rank]) out << b.theBoard[file][rank]->getRepn();
      else if ((file + rank) % 2) out << ' ';
      else out << '_';
    }
    out << endl;
  }
  out << endl << "  abcdefgh";
  return out;
}
