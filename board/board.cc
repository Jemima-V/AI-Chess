include "board.h"

void Board:: Board()

void Board:: initBoard(){
    //insert Black side
    boards[0][0]= new .... ;
    //Pawns
    for(int i = 0; i < 8; i++){
        boards[1][i]= new Pawn{black}; //pointer to pawn
    }
    

    //insert White side
    boards[6][0]= new ... ;
    
    //pawns
    for(int i = 0; i < 8; i++){
        boards[1][i]= new Pawn{white}; //pointer to pawn
    }
}

  explicit Board();
  void Board();
  &Board getCurrBoard();
  
  bool checkRow(*Piece from, *Piece to);
  bool checkCol(*Piece from, *Piece to);
  bool checkDiagonal(*Piece from, *Piece to);
  void display();
  
  /*
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  */
  ~Board();

  &Piece getState(int row, int col) const; //DO WE WANT IT TO RETURN THE PEICE AT THE COORD? OR THE WHOLE BOARD

