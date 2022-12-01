#include "board.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "pieces.h"

#include <vector>
#include <memory>

using namespace std;

Board:: Board(){
    //currBoard(8, (vector<Piece*>(8, nullptr))); 
    for (int i = 0; i < 8; i++){
        //currBoard.push_back(std::vector<unique_ptr<Pieces>>{});
        currBoard.push_back(vector<Pieces*>{});
        for(int j = 0; j < 8; j++){
            currBoard[i].emplace_back(nullptr);
            //currBoard[i][j] = nullptr;
        }
    }
    
    whiteKing.file = 4;
    whiteKing.rank = 0;
    blackKing.file = 4;
    blackKing.rank = 7;
}

  //dtor 
Board:: ~Board(){/*
    //iterate over the 2D vector and delete each piece pointer it contains
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete currBoard[i][j];
        }
    }

    delete currBoard;*/
}

void Board:: initBoard(){
    int white = 1; //player 1
    int black = 2; //player 2
    
    //WHITE SIDE
    for(int i = 0; i < 8; i++){

        //Rooks
        if(i == 0 || i == 7){
            currBoard[i][0]= new Rook{white, false, 'R'};
            //currBoard[i][0]= unique.ptr<Peices> {new Rook {white, false, 'R'}};
            
        
        //Knights
        } else if (i == 1 || i == 6){
            currBoard[i][0]= new Knight{white, false, 'N'};

        //Bishops
        } else if ( i == 2 || i == 5){
            currBoard[i][0]= new Bishop{white, false, 'B'};
        
        //King
        } else if (i == 4){
            currBoard[i][0]= new King{white, false, 'K'};
            //whiteKing.rank = 7;
            //whiteKing.file = i;
        
        //Queen
        } else {
            currBoard[i][0]= new Queen{white, false, 'Q'};
        }
    }

    //Pawns
    for(int i = 0; i < 8; i++){
        currBoard[i][1]= new Pawn{white, false, 'P', true};
    }

    //BLACK SIDE
    for(int i = 0; i < 8; i++){

        //Rooks
        if(i == 0 || i == 7){
            currBoard[i][7]= new Rook{black, false, 'r'};
        
        //Knights
        } else if (i == 1 || i == 6){
            currBoard[i][7]= new Knight{black, false, 'n'};

        //Bishops
        } else if ( i == 2 || i == 5){
            currBoard[i][7]= new Bishop{black, false, 'b'};
        
        //King
        } else if (i == 4){
            currBoard[i][7]= new King{black, false, 'k'};
            //blackKing.rank = 0;
            //blackKing.file = i; //initialed in ctor

        //Queen
        } else {
            currBoard[i][7]= new Queen{black, false, 'q'};
        }
    }

    //Pawns
    for (int i = 0; i < 8; i++){
        currBoard[i][6]= new Pawn{black, false, 'p', true};
    }

    
}

  //Get the state of each position on the board for rendering
char Board:: getState(int file, int rank) const{
    if(currBoard[file][rank] != nullptr){
        char id = currBoard[file][rank]->getId();
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
Pieces* Board:: pieceAt(Position pos){
    return currBoard[pos.file][pos.rank];
}

Position Board:: getWhiteKing(){
    return whiteKing;
}

Position Board:: getBlackKing(){
    return blackKing;
}

bool Board:: checkRow(Position from, Position to){

    //make sure kriti only sends positions from the same rows (.rank is the same)
    //Make sure kriti checks start and from are not the same position
    //rightward direction
    if (from.file < to.file){

        //Loop through the row and check for any pieces in the way
        for(int i = from.file; i <= to.file; i++){
            if (currBoard[i][from.rank] != nullptr){
                return false;
            }
        }

        //if this line is reached there is no piece blocking the path
        return true;
    
    //case where from.file > to.file
    //leftward direction
    } else {

        //Loop through the row and check for any pieces in the way
        for(int i = from.file; i >= to.file; i--){
            if (currBoard[i][from.rank] != nullptr){
                return false;
            }
        }

        //if this line is reached there is no piece blocking the path
        return true;
    }
    
}

bool Board:: checkCol(Position from, Position to){

    //Make sure kriti only sends values from the same column (.file is the same)
    //Make sure kriti checks start and from are not the same position
    //Upwards direction
    if (from.rank < to.rank){

        //Loop through the column and check for any pieces in the way
        for(int i = from.rank; i <= to.rank; i++){
            if (currBoard[from.file][i] != nullptr){
                return false;
            }
        }

        //if this line is reached there is no piece blocking the path
        return true;
    
    //case where from.rank > to.rank => downwards direction
    } else {

        //Loop through the row and check for any pieces in the way
        for(int i = from.rank; i >= to.rank; i--){
            if (currBoard[from.file][i] != nullptr){
                return false;
            }
        }

        //if this line is reached there is no piece blocking the path
        return true;
    }

}

bool Board:: checkDiagonal(Position from, Position to){
    
    //check if kriti is only sending positions that are diagonal to each other
    //Direction => Upwards to the right
    if(from.rank < to.rank && from.file < to.file){
        
        for(int i = from.rank, j = from.file; i <= to.rank && j <= to.file; i++, j++){

            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => Upwards to the left
    } else if (from.rank < to.rank && from.file > to.file){

        for(int i = from.rank, j = from.file; i <= to.rank && j >= to.file; i++, j--){

            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => Downwards to right
    } else if (from.rank > to.rank && from.file < to.file){

         for(int i = from.rank, j = from.file; i >= to.rank && j <= to.file; i--, j++){

            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => downwards to the left
    //from.rank > to.rank && from.file > to.file
    } else{

         for(int i = from.rank, j = from.file; i >= to.rank && j >= to.file; i--, j--){

            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    }
}

Position Board:: checkRowOpp(int owner, Position from, Position to){
    Position p{-1, -1};

    //rightward direction
    if (from.file < to.file){

        //Loop through the row and check for any pieces in the way
        for(int i = from.file; i <= to.file; i++){
            if (currBoard[i][from.rank] != nullptr && currBoard[i][from.rank]->getOwner() != owner){
                //return currBoard[from.rank][i];
                p.rank = from.rank;
                p.file = i;
                return p;
            }
        }

        //if this line is reached there is no piece blocking the path
        p.rank = -1;
        p.file = -1;
        return p;
        //return nullptr;
    
    //case where from.file > to.file
    //leftward direction
    } else {

        //Loop through the row and check for any pieces in the way
        for(int i = from.file; i >= to.file; i--){
            if (currBoard[i][from.rank] != nullptr && currBoard[i][from.rank]->getOwner() != owner){
                //return currBoard[from.rank][i];
                p.rank = from.rank;
                p.file = i;
                return p;
            }
        }

        //if this line is reached there is no piece blocking the path
        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;
    }
}

Position Board:: checkColOpp(int owner, Position from, Position to){
    Position p{-1, -1};

    //Upwards direction
    if (from.rank < to.rank){

        //Loop through the column and check for any pieces in the way
        for(int i = from.rank; i <= to.rank; i++){
            if (currBoard[from.file][i] != nullptr && currBoard[from.file][i]->getOwner() != owner){
                //return currBoard[i][from.file];
                p.rank = i;
                p.file = from.file;
                return p;
                
            }
        }

        //if this line is reached there is no piece blocking the path
        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;
    
    //case where from.rank > to.rank => downwards direction
    } else {

        //Loop through the row and check for any pieces in the way
        for(int i = from.rank; i >= to.rank; i--){
            if (currBoard[from.file][i] != nullptr && currBoard[from.file][i]->getOwner() != owner){
                //return currBoard[i][from.file];
                p.rank = i;
                p.file = from.file;
                return p;
            }
        }

        //if this line is reached there is no piece blocking the path
        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;
    }
}

Position Board:: checkDiagOpp(int owner, Position from, int direction){
    Position p{-1, -1};
    int upLeft = 1;
    int downLeft = 2;
    int upRight = 3;
    int downRight = 4;

    int maxFile = 7;
    int minFile = 0;
    int maxRank = 7;
    int minRank = 0;


    //Direction => Upwards to the right
    if(direction == upRight){
        
        for(int i = from.rank, j = from.file; i <= maxRank && j <= maxFile; i++, j++){

            if(currBoard[j][i] != nullptr && currBoard[j][i]->getOwner() != owner){
                //return currBoard[i][j];
                p.rank = i;
                p.file = j;
                return p;
            }

        }

        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;

    //Direction => Upwards to the left
    } else if (direction == upLeft){

        for(int i = from.rank, j = from.file; i <= maxRank && j >= minFile; i++, j--){

            if(currBoard[j][i] != nullptr && currBoard[j][i]->getOwner() != owner){
                //return currBoard[i][j];
                p.rank = i;
                p.file = j;
                return p;
            }

        }

        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;

    //Direction => Downwards to right
    } else if (direction == downRight){

         for(int i = from.rank, j = from.file; i >= minRank && j <= maxFile; i--, j++){

            if(currBoard[j][i] != nullptr && currBoard[j][i]->getOwner() != owner){
                //return currBoard[i][j];
                p.rank = i;
                p.file = j;
                return p;
            }

        }

        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;

    //Direction => downwards to the left
    //from.rank > to.rank && from.file > to.file
    } else{

         for(int i = from.rank, j = from.file; i >= minRank && j >= minFile; i--, j--){

            if(currBoard[j][i] != nullptr && currBoard[j][i]->getOwner() != owner){
                //return currBoard[i][j];
                p.rank = i;
                p.file = j;
                return p;
            }

        }

        //return nullptr;
        p.rank = -1;
        p.file = -1;
        return p;

    }
}




//TALK OVER WITH MALVIKA
//alter the main board to reflect the move -> set old location to null, new position to the piece
void Board:: makeMove(Pieces *p, Position posOld, Position posNew){
    //dont forget to update the whiteking/black king if it is moved
    if(p->getId() == 'K'){
        whiteKing.file = posNew.file;
        whiteKing.rank = posNew.rank;
    } else if (p->getId() == 'k'){
        blackKing.file == posNew.file;
        blackKing.rank == posNew.rank;
    }

    //DOUBLE CHECK FOR MEMORY LEAK?
    currBoard[posNew.file][posNew.rank] = p;
    currBoard[posOld.file][posOld.rank] = nullptr;
}

void Board::place(Pieces* addPiece, Position pos){
    //double check with malvike that she checks if there is anything already at the position
    //DOUBLE CHECK FOR MEMORY LEAKS 
    currBoard[pos.file][pos.rank] = addPiece;
}
  
void Board::removePiece(Position pos){
    currBoard[pos.file][pos.rank] = nullptr;
}

  
void Board::render(){
    notifyObservers();
}

