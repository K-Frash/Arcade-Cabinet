#include <iostream>
#include <string>
#include "colours.h"
#include "board.h"
#include "piece.h"
#include "human.h"
#include "computer1.h"
using namespace std;

int main() {
  Board b;
  Player *player1 = 0, *player2 = 0, *activePlayer = 0;
  float whiteScore = 0, blackScore = 0;

  char f, f2;
  int r, r2;

  string command;
  bool wasSetup = false;

  while(cin >> command) {
    if (command == "setup") {
      b.clear();
      cout << b << endl;
      while (cin >> command) {
        if (command == "+") {
          char pc;
          if (!(cin >> pc >> f >> r)) break;
          if(b.addPiece(pc, f - 'a', r - 1))
            cout << b << endl;
        }
        else if (command == "-") {
          if (!(cin >> f >> r)) break;
          b.removePiece(f - 'a', r - 1);
          cout << b << endl;
        }
        else if (command == "=") {
          string col;
          if (!(cin >> col)) break;
          if (col == "White" || col == "white") b.setTurn(White);
          if (col == "Black" || col == "black") b.setTurn(Black);
        }
        else if (command == "done") {
          if (b.verify()) break;
        }
      }
      wasSetup = true;
    }
    if (command == "game") {
      if (!wasSetup) {
        b.init();
      }
      wasSetup = false;
      cout << b << endl;

      string wPlayer, bPlayer;
      if (!(cin >> wPlayer >> bPlayer)) break;
      delete player1;
      if (wPlayer == "human") player1 = new Human;
      else if (wPlayer == "computer1") player1 = new Computer1(b);

      delete player2;
      if (bPlayer == "human") player2 = new Human;
      else if (bPlayer == "computer1") player2 = new Computer1(b);

      activePlayer = player1;
      
      try {
        while (cin >> command) {
          if (command == "moves") {
            if (!(cin >> f >> r)) break;
            int file = f - 'a';
            int rank = r - 1;
            const Piece *p = b.pieceAt(file, rank);
            if (!p) {
              cout << "No piece on " << make_pair(file, rank) << "." << endl;
            }
            else {
              printLegalMoves(cout, make_pair(file, rank), p->getMoves()) << endl;
            }
         }
         if (command == "move") {
           pair<Posn,Posn> mv = activePlayer->getMove();
           f = mv.first.first;
           r = mv.first.second;
           f2 = mv.second.first;
           r2 = mv.second.second;
           if (!*activePlayer) break;
           const Piece *p = b.pieceAt(f - 'a', r - 1);
           if (!p) {
             cout << "No piece on " << make_pair(f - 'a', r - 1) << "." << endl;
           }
           else if (p->getColour() != b.getTurn()) {
             cout << "Wrong piece colour" << endl;
           }
           else {
             bool legal = false;
             try {
               legal = b.move(f, r, f2, r2);
             }
             catch (Promote) {
               b.promote(activePlayer->promote());
               legal = true;
             }
             if (!legal) {
               cout << "Illegal" << endl;
             }
             else {
               cout << b << endl;
               if (b.check(White)) {
                 cout << "White is in check." << endl;
               }
               if (b.check(Black)) {
                 cout << "Black is in check." << endl;
               }
               activePlayer = activePlayer == player1 ? player2 : player1;
             }
           }
         }
         else if (command == "resign") {
           cout << (b.getTurn() == White ? "Black" : "White") << " wins!" << endl;
           b.getTurn() == White ? ++blackScore : ++whiteScore;
           break;
         }
       }
      }
      catch(Checkmate) {
        cout << b << endl;
        cout << "Checkmate! ";
        cout << (b.getTurn() == White ? "Black" : "White") << " wins!" << endl;
        b.getTurn() == White ? ++blackScore : ++whiteScore;
      }
      catch(Stalemate) {
        cout << b << endl;
        cout << "Stalemate! ";
        whiteScore += .5;
        blackScore += .5;
      }
    }
  }
  delete player1;
  delete player2;
  cout << "Final Score:" << endl;
  cout << "White: " << whiteScore << endl;
  cout << "Black: " << blackScore << endl;
}
