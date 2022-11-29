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
        //currBoard.push_back(std::vector<Piece*>{});
        for(int j = 0; j < 8; j++){
            //currBoard[1].emplace_back(nullptr);
            currBoard[i][j] = nullptr;
            //currBoard.emplace_back(nullptr)
        }
    }

    whiteKing.rank = 0;
    whiteKing.file = 4;
    blackKing.rank = 7;
    blackKing.file = 4;
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

void Board:: initBoard(){
    int white = 1; //player 1
    int black = 2; //player 2
    
    //WHITE SIDE
    for(int i = 0; i < 8; i++){

        //Rooks
        if(i == 0 || i == 7){
            currBoard[0][i]= new Rook{white, false, 'R'};
        
        //Knights
        } else if (i == 1 || i == 6){
            currBoard[0][i]= new Knight{white, false, 'N'};

        //Bishops
        } else if ( i == 2 || i == 5){
            currBoard[0][i]= new Bishop{white, false, 'B'};
        
        //King
        } else if (i == 4){
            currBoard[0][i]= new King{white, false, 'K'};
            //whiteKing.rank = 7;
            //whiteKing.file = i;
        
        //Queen
        } else {
            currBoard[0][i]= new Queen{white, false, 'Q'};
        }
    }

    //Pawns
    for(int i = 0; i < 8; i++){
        currBoard[1][i]= new Pawn{white, false, 'P', true};
    }

    //BLACK SIDE
    for(int i = 0; i < 8; i++){

        //Rooks
        if(i == 0 || i == 7){
            currBoard[7][i]= new Rook{black, false, 'r'};
        
        //Knights
        } else if (i == 1 || i == 6){
            currBoard[7][i]= new Knight{black, false, 'n'};

        //Bishops
        } else if ( i == 2 || i == 5){
            currBoard[7][i]= new Bishop{black, false, 'b'};
        
        //King
        } else if (i == 4){
            currBoard[7][i]= new King{black, false, 'k'};
            //blackKing.rank = 0;
            //blackKing.file = i; //initialed in ctor

        //Queen
        } else {
            currBoard[7][i]= new Queen{black, false, 'q'};
        }
    }

    //Pawns
    for (int i = 0; i < 8; i++){
        currBoard[6][i]= new Pawn{black, false, 'p', true};
    }

    
}

  //Get the state of each position on the board for rendering
char Board:: getState(int rank, int file) const{
    if(currBoard[rank][file] != nullptr){
        char id = currBoard[rank][file]->getId();
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
    return currBoard[pos.rank][pos.file];
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
            if (currBoard[from.rank][i] != nullptr){
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
            if (currBoard[from.rank][i] != nullptr){
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
            if (currBoard[i][from.file] != nullptr){
                return false;
            }
        }

        //if this line is reached there is no piece blocking the path
        return true;
    
    //case where from.rank > to.rank => downwards direction
    } else {

        //Loop through the row and check for any pieces in the way
        for(int i = from.rank; i >= to.rank; i--){
            if (currBoard[i][from.file] != nullptr){
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

            if(currBoard[i][j] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => Upwards to the left
    } else if (from.rank < to.rank && from.file > to.file){

        for(int i = from.rank, j = from.file; i <= to.rank && j >= to.file; i++, j--){

            if(currBoard[i][j] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => Downwards to right
    } else if (from.rank > to.rank && from.file < to.file){

         for(int i = from.rank, j = from.file; i >= to.rank && j <= to.file; i--, j++){

            if(currBoard[i][j] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => downwards to the left
    //from.rank > to.rank && from.file > to.file
    } else{

         for(int i = from.rank, j = from.file; i >= to.rank && j >= to.file; i--, j--){

            if(currBoard[i][j] != nullptr){
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
            if (currBoard[from.rank][i] != nullptr && currBoard[from.rank][i]->getOwner() != owner){
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
            if (currBoard[from.rank][i] != nullptr && currBoard[from.rank][i]->getOwner() != owner){
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
            if (currBoard[i][from.file] != nullptr && currBoard[i][from.file]->getOwner() != owner){
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
            if (currBoard[i][from.file] != nullptr && currBoard[i][from.file]->getOwner() != owner){
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

Postion Board:: checkDiagOpp(int owner, Position from, Position to){
    Position p{-1, -1};

    //Direction => Upwards to the right
    if(from.rank < to.rank && from.file < to.file){
        
        for(int i = from.rank, j = from.file; i <= to.rank && j <= to.file; i++, j++){

            if(currBoard[i][j] != nullptr && currBoard[i][j]->getOwner() != owner){
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
    } else if (from.rank < to.rank && from.file > to.file){

        for(int i = from.rank, j = from.file; i <= to.rank && j >= to.file; i++, j--){

            if(currBoard[i][j] != nullptr && currBoard[i][j]->getOwner() != owner){
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
    } else if (from.rank > to.rank && from.file < to.file){

         for(int i = from.rank, j = from.file; i >= to.rank && j <= to.file; i--, j++){

            if(currBoard[i][j] != nullptr && currBoard[i][j]->getOwner() != owner){
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

         for(int i = from.rank, j = from.file; i >= to.rank && j >= to.file; i--, j--){

            if(currBoard[i][j] != nullptr && currBoard[i][j]->getOwner() != owner){
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
    currBoard[posNew.rank][posNew.file] = p;
    currBoard[posOld.rank][posOld.rank] = nullptr;
}

void Board::place(Pieces* addPiece, Position pos){
    //double check with malvike that she checks if there is anything already at the position
    currBoard[pos.rank][pos.file] = addPiece;
}
  
void Board::removePiece(Position pos){
    currBoard[pos.rank][pos.file];
}

  
void Board::render(){
    notifyObservers();
}

