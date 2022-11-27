#include "board.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "pieces.h"

#include <vector>
//using namespace std;

Board:: Board(){
    //currBoard(8, (vector<Piece*>(8, nullptr))); 
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            currBoard[i][j] = nullptr;
            //currBoard.emplace_back(nullptr)
        }
    }
}

void Board:: initBoard(){
    int white = 1; //player 1
    int black = 2; //player 2

    //Piece IDs: first digit represents the colour, 2nd digit represents the type of piece
    // rooks => 1, Knights =>2, Bishops => 3, Kings => 4, Queens => 5, Pawns => 6
    // these will be usefull when rendering and we need to know Piece types
    /*
    int whiteRookID = 11;
    int whiteKnightID = 12;
    int whiteBishopID = 13;
    int whiteKingID = 14;
    int whiteQueenID = 15;
    int whitePawnID = 16;

    int blackRookID = 21;
    int blackKnightID = 22;
    int blackBishopID = 23;
    int blackKingID = 24;
    int blackQueenID = 25;
    int blackPawnID = 26;

    currboard[0][0]= new Rook;
    currboard[0][1]= new Knight;
    currboard[0][2]= new Bishop;
    currboard[0][3]= new King;
    currboard[0][4]= new Queen;
    currboard[0][5]= new Bishop;
    currboard[0][6]= new Knight;
    currboard[0][7]= new Rook;
    */
    
    //WHITE SIDE
    for(int i = 0; i < 7; i++){

        //Rooks
        if(i == 0 || i == 7){
            currBoard[6][i]= new Rook{white, false, 'R'};
        
        //Knights
        } else if (i == 1 || i == 6){
            currBoard[6][i]= new Knight{white, false, 'N'};

        //Bishops
        } else if (i == 2 || i = 5){
            currBoard[6][i]= new Bishop{white, false, 'B'};
        
        //King
        } else if (i == 4){
            currBoard[6][i]= new King{white, false, 'K'};
        
        //Queen
        } else {
            currBoard[6][i]= new Queen{white, false, 'Q'};
        }
    }

    //Pawns
    for(int i = 0; i < 8; i++){
        currBoard[6][i]= new Pawn{white, false, "P", true, false};
    }

    //BLACK SIDE -> owner = player1
    for(int i = 0; i < 7; i++){

        //Rooks
        if(i == 0 || i == 7){
            currBoard[0][i]= new Rook{black, false, 'r'};
        
        //Knights
        } else if (i == 1 || i == 6){
            currBoard[0][i]= new Knight{black, false, 'n'};

        //Bishops
        } else if (i == 2 || i = 5){
            currBoard[0][i]= new Bishop{black, false, 'b'};
        
        //King
        } else if (i == 3){
            currBoard[0][i]= new King{black, false, 'k'};
        
        //Queen
        } else {
            currBoard[0][i]= new Queen{black, false, 'q'};
        }
    }

    //Pawns
    for(int i = 0; i < 8; i++){
        currBoard[1][i]= new Pawn{black, false, 'p', true, false};
    }

    
}

  //Get the state of each position on the board for rendering
  char Board:: getState(int rank, int file) const{
    if(currBoard[rank][file] != nullptr){
        int id = currBoard[rank][file]->getId();
        return id;
    } else{
        return 'X';
    }
  }

  /*
  &Board getCurrBoard(){
    return *currBoard;
  }
  */

  //alter the main board to reflect the move -> set old location to null, new position to the piece
  void makeMove(Piece *p, Position posOld, Position posNew){
    currBoard[posNew.rank][posNew.file] = p;
    currBoard[posOld.rank][posOld.rank] = nullptr;
  }
  
  //dtor 
  Board:: ~Board(){
    //iterate over the 2D vector and delete each piece pointer it contains
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete currBoard[i][j];
        }
    }

    delete currBoard;
  }
