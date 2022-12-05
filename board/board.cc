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

//Board Ctor
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

//Board copy constructor
//call default ctor in MIL to initalize vector
Board::Board(const Board &other): Board{}{
//cout << "Enter copy ctor" << endl;
    whiteKing.file = other.whiteKing.file;
    whiteKing.rank = other.whiteKing.rank;
    blackKing.file = other.blackKing.file;
    blackKing.rank = other.blackKing.rank;
    
    //loop through 2D vector and call pieces copy 
    for (int i = 0; i < 8; i++){
        
        for(int j = 0; j < 8; j++){

            //make sure we dont call makeCopy() on an empty position
            if(other.currBoard[i][j] != nullptr){
                
                //cout << "Before Makecopy" << endl;
                //cout << other.currBoard[i][j]->getId() << endl;
                
                
                //cout << i << j << endl;
                currBoard[i][j] = other.currBoard[i][j]->makeCopy();
                //cout << currBoard[i][j]->getId() << endl;
                //cout << "after makeCopy" << endl;
            } else {
                currBoard[i][j] = nullptr;
            }
            
        }

    }

    //cout << "Exit copy" << endl;
}

  //dtor 
Board:: ~Board(){
    //iterate over the 2D vector and delete each piece pointer it contains
    cout << "Enter Dtor" << endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            delete currBoard[i][j];
        }
    }

    //delete currBoard;*/
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
        for(int i = from.file + 1; i < to.file; i++){
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
        for(int i = from.file - 1; i > to.file; i--){
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
        for(int i = from.rank + 1; i < to.rank; i++){
            if (currBoard[from.file][i] != nullptr){
                return false;
            }
        }

        //if this line is reached there is no piece blocking the path
        return true;
    
    //case where from.rank > to.rank => downwards direction
    } else {

        //Loop through the row and check for any pieces in the way
        for(int i = from.rank - 1; i > to.rank; i--){
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
    //THIS ALSO CHECKS
    //Direction => Upwards to the right
    if(from.rank < to.rank && from.file < to.file){
        for(int i = from.rank + 1, j = from.file + 1; i < to.rank && j < to.file; i++, j++){
            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => Upwards to the left
    } else if (from.rank < to.rank && from.file > to.file){
        for(int i = from.rank + 1, j = from.file - 1; i < to.rank && j > to.file; i++, j--){

            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => Downwards to right
    } else if (from.rank > to.rank && from.file < to.file){
         for(int i = from.rank - 1, j = from.file + 1; i > to.rank && j < to.file; i--, j++){

            if(currBoard[j][i] != nullptr){
                return false;
            }

        }

        return true;

    //Direction => downwards to the left
    //from.rank > to.rank && from.file > to.file
    } else{
         for(int i = from.rank - 1, j = from.file - 1; i > to.rank && j > to.file; i--, j--){

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





//alter the main board to reflect the move -> set old location to null, new position to the piece
void Board:: makeMove(Pieces *p, Position posOld, Position posNew){
    
    //update the whiteking/black king if it is moved
    //update if a white king moves
    if(p->getId() == 'K'){
        whiteKing.file = posNew.file;
        whiteKing.rank = posNew.rank;

    //update if a black king moves
    } else if (p->getId() == 'k'){
        blackKing.file = posNew.file;
        blackKing.rank = posNew.rank;
    }

    //check if new position is already occuppied (if the move will cause a capture)
    //capturing move
    if(currBoard[posNew.file][posNew.rank] != nullptr){
        delete currBoard[posNew.file][posNew.rank];
    }

    currBoard[posNew.file][posNew.rank] = p;

    //removePiece(posOld);
    //delete currBoard[posOld.file][posOld.rank];
    currBoard[posOld.file][posOld.rank] = nullptr;
    
}

void Board::place(Pieces* addPiece, Position pos){
    //double check with malvike that she checks if there is anything already at the position
    //DOUBLE CHECK FOR MEMORY LEAKS 

    if(currBoard[pos.file][pos.rank] != nullptr){
        //ASK BRAD -> SINCE CURRBOARD IS A VECTOR DO I STILL DELETE THE PIECE THAT IS BEING CAPTURED??
        delete currBoard[pos.file][pos.rank];
    }
    
    currBoard[pos.file][pos.rank] = addPiece;
}
  
void Board::removePiece(Position pos){
    delete currBoard[pos.file][pos.rank];
    currBoard[pos.file][pos.rank] = nullptr;
}

  
void Board::render(){
    cout << "enter render" << endl;
    notifyObservers();
}

/*void Board::renderText(){
    notifyText();
}*/

void Board::renderMove(int x1, int x2, int y1, int y2){
    notifyMove(x1, x2, y1, y2);
}

bool Board::inBounds(Position pos){
    if(pos.file > 7 || pos.file < 0 || pos.rank > 7 || pos.rank < 0){
        return false;
    } else{
        return true;
    }
}

bool Board::isOppKnightAt(Position tempPos, int curOwner){
    
    //check if the case is in bounds and that there is a piece that is of the opponent
    if(inBounds(tempPos) && pieceAt(tempPos) != nullptr && pieceAt(tempPos)->getOwner() != curOwner){
        //check if that piece is a knight
        if( pieceAt(tempPos)->getId() == 'n' || pieceAt(tempPos)->getId() == 'N'){
            return true;
        }

    } else {
        return false;
    }
}

//specifally for kingInCheck function to check for sourrounding horses that can attack my king
bool Board::checkL(Position start){

    //KRITI CANT SEND ME A STARTING POSITION THAT DOES NOT HAVE A PIECE AT THE LOCATION
    int curOwner = pieceAt(start)->getOwner();
    Position tempPos{-1,-1};


    //case A
    tempPos.file = start.file + 1;
    tempPos.rank = start.rank + 2;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }


    //case B
    tempPos.file = start.file + 2;
    tempPos.rank = start.rank + 1;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    //case C
    tempPos.file = start.file + 2;
    tempPos.rank = start.rank - 1;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    //case D
    tempPos.file = start.file + 1;
    tempPos.rank = start.rank - 2;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    //case E
    tempPos.file = start.file - 1;
    tempPos.rank = start.rank - 2;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    //case F
    tempPos.file = start.file - 2;
    tempPos.rank = start.rank - 1;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    //case G
    tempPos.file = start.file - 2;
    tempPos.rank = start.rank + 1;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    //case H
    tempPos.file = start.file - 1;
    tempPos.rank = start.rank + 2;

    if(isOppKnightAt(tempPos, curOwner)){
        return true;
    }

    return false;
}

//ASK KRITI HOW THESE POINTERS ARE GONNA GET DELETED??
vector<Position> Board::getPiecePositions(int owner){
    vector<Position> posVec;
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(currBoard[i][j] != nullptr && currBoard[i][j]->getOwner() == owner){
                Position p{i,j};
                posVec.emplace_back(p);
            }
        }
    }

    return posVec;
}

void Board::boardSetup() {
    while (true) {
        string command;
        cin >> command;
        if (command == "done") {
            setupDone = true;
            break;
        }
        else if (command == "+") {
            cout << "adding piece" << endl;
            char piece;
            string square;
            cin >> piece >> square;
            Pieces *piecePlace = createPiece(piece);
            //converting square into a position struct
            Position p = convert(square); 
            //if there is an exisiting piece at that position
            if (gameboard->pieceAt(p) != nullptr) {
                gameboard->place(piecePlace, p); //board handles case for replacing piece
            }
            //if the position is a null pointer 
            else {
                gameboard->place(piecePlace, p);
            }
            cout << "piece added" << endl;
            gameboard->render(); //displays board
            cout << "after render" << endl;
        }
        else if (command == "-") {
            string square;
            cin >> square;
            //converting square into a position struct
            Position p = convert(square);
            if (gameboard->pieceAt(p) != nullptr) {
                gameboard->removePiece(p); //board handles case for removing piece at position
                gameboard->render(); //displays board
            } 
            else {
                continue; //if position is a nullptr
            }
        }
        else if (command == "=") {
            string colour;
            cin >> colour;
            firstTurn = colour;
        } 
        else {
            continue; //continues with command loop if any command is misspelled
        }
    }
}

