#include <iostream>
#include "chess.h"

Board::Board(int Size){
    for(int i=0; i<Size; i++){
        vector<Piece> temp;
        for(int j=0;j<Size;j++){
            temp.push_back(Piece(EMPTY));
        }
        this->board.push_back(temp);
    }
}

void Board::printBoard(){
    int row=0, col=0;

    cout<<endl;
    for(int i=0; i <= 2*this->Size(); i++){
        for(int j=0; j<=2*this->Size(); j++){
            if(i%2==0)
            {
                if(j%2==0)
                    cout<<" ";
                else cout<<"---";
            }
            else{
                if(j%2==0)
                    cout<<"|";
                else{
                    cout<<" "<<(char)this->getSquare(Position(row,col))<<" ";
                    col++;
                    if(col==this->Size()){
                        row++; col=0;
                    }
                }
            }
        }
        cout<<endl;
    }
}

bool Board::isAttacked(Position pos, Piece placing){
    //vertically and horizontally, can be attacked by queen or rook
    for (int i = 0; i < this->Size(); i++) {
        if (this->getSquare(pos.row, i) == QUEEN || this->getSquare(i, pos.col) == QUEEN || this->getSquare(pos.row, i) == ROOK || this->getSquare(i, pos.col) == ROOK)
            return true;
    }

    //up-right
    //can be attacked by queen or bishop
    //also, bishop that is being placed can attack rook on diagonal
    int i=pos.row, j=pos.col;
    while(j<this->Size() && i>=0){
        if (this->getSquare(i,j) == QUEEN || this->getSquare(i,j) == BISHOP)
            return true;
        if(placing == BISHOP && this->getSquare(i,j) == ROOK)
            return true;
    i--; j++;
    }

    //up-left, same as up-right
    i=pos.row, j=pos.col;
    while(j>=0 && i>=0){
        if (this->getSquare(i,j) == QUEEN || this->getSquare(i,j) == BISHOP)
            return true;
        if(placing == BISHOP && this->getSquare(i,j) == ROOK)
            return true;
    i--; j--;
    }

    //down-right, same as before ones
    i=pos.row, j=pos.col;
    while(j<this->Size() && i<this->Size()){
        if (this->getSquare(i,j) == QUEEN || this->getSquare(i,j) == BISHOP)
            return true;
        if(placing == BISHOP && this->getSquare(i,j) == ROOK)
            return true;
    i++; j++;
    }

    //down-left, same as before ones
    i=pos.row, j=pos.col;
    while(j>=0 && i<this->Size()){
        if (this->getSquare(i,j) == QUEEN || this->getSquare(i,j) == BISHOP)
            return true;
        if(placing == BISHOP && this->getSquare(i,j) == ROOK)
            return true;
    i++; j--;
    }

    //if king is being placed, he can be attacked by knight
    if(placing == KING){
        int i=pos.row;
        int j=pos.col;
        if(i-2>=0 && j-1>=0) //up two, left one
            if(this->getSquare(i-2,j-1) == KNIGHT)
                return true;

        if(i-1>=0 && j-2>=0) //up one, left two
            if(this->getSquare(i-1,j-2) == KNIGHT)
                return true;

        if(i+1<this->Size() && j-2>=0) //down one, left two
            if(this->getSquare(i+1,j-2) == KNIGHT)
                return true;

        if(i-2>=0 && j+1<this->Size()) //up two, right one
            if(this->getSquare(i-2,j+1) == KNIGHT)
                return true;

        if(i+2<this->Size() && j-1>=0) //down two, left one
            if(this->getSquare(i+2,j-1) == KNIGHT)
                return true;

        if(i-1>=0 && j+2<this->Size()) //up one, right two
            if(this->getSquare(i-1,j+2) == KNIGHT)
                return true;

        if(i+2<this->Size() && j+1<this->Size()) //down two, right one
            if(this->getSquare(i+2,j+1) == KNIGHT)
                return true;

        if(i+1<this->Size() && j+2<this->Size()) //down one, right two
            if(this->getSquare(i+1,j+2) == KNIGHT)
                return true;
    }

    //everyone is safe
    return false;
}

bool Board::isAttacking(Position pos, Piece piece){
    if(piece == QUEEN){
        isQueenAttacking(pos);
    }
    else if(piece == ROOK){
        isRookAttacking(pos);
    }
    else if(piece == BISHOP){
        isBishopAttacking(pos);
    }
    else if(piece == KNIGHT){
        isKnightAttacking(pos);
    }
    else if(piece == KING){
        isKingAttacking(pos);
    }
}

bool Board::isQueenAttacking(Position pos){
    //for queens, it is enough to check only if she attacks a previous one, because they are placed first

    //vertically and horizontally
    for (int i = 0; i < this->Size(); i++) {
        if (this->getSquare(pos.row,i) != EMPTY || this->getSquare(i,pos.col) != EMPTY)
            return true;
    }

    //up-right
    int i=pos.row, j=pos.col;
    while(j<this->Size() && i>=0){
        if (this->getSquare(i,j) != EMPTY)
         return true;
    i--; j++;
    }

    //up-left
    i=pos.row, j=pos.col;
    while(j>=0 && i>=0){
        if (this->getSquare(i,j) != EMPTY)
         return true;
    i--; j--;
    }

    //down-right
    i=pos.row, j=pos.col;
    while(j<this->Size() && i<this->Size()){
        if (this->getSquare(i,j) != EMPTY)
         return true;
    i++; j++;
    }

    //down-left
    i=pos.row, j=pos.col;
    while(j>=0 && i<this->Size()){
        if (this->getSquare(i,j) != EMPTY)
         return true;
    i++; j--;
    }

    //the queen does not attack the previous ones
    return false;
}

bool Board::isRookAttacking(Position pos){
    //rook is placed second in order
    //it is enough to check is he attacked by queen or another rook
    return this->isAttacked(pos, ROOK);
}

bool Board::isBishopAttacking(Position pos){
    //bishop is placed third in order
    //it is enough to check is he attacked by queen or rook (if queen attacks him, then he also attacks her)
    //also, it is necessary to check if he attacks rook
    return this->isAttacked(pos, BISHOP);
}

bool Board::isKnightAttacking(Position pos){
    //knight is placed fourth in order
    //for knights it is necessary to check if they attack other figures, and then of course does other figures attacks him
    int i=pos.row;
    int j=pos.col;
    if(i-2>=0 && j-1>=0) //up two, left one
        if(this->getSquare(i-2,j-1) != EMPTY)
            return true;

    if(i-1>=0 && j-2>=0) //up one, left two
        if(this->getSquare(i-1,j-2) != EMPTY)
            return true;

    if(i+1<this->Size() && j-2>=0) //down one, left two
        if(this->getSquare(i+1,j-2) != EMPTY)
            return true;

    if(i-2>=0 && j+1<this->Size()) //up two, right one
        if(this->getSquare(i-2,j+1) != EMPTY)
            return true;

    if(i+2<this->Size() && j-1>=0) //down two, left one
        if(this->getSquare(i+2,j-1) != EMPTY)
            return true;

    if(i-1>=0 && j+2<this->Size()) //up one, right two
        if(this->getSquare(i-1,j+2) != EMPTY)
            return true;

    if(i+2<this->Size() && j+1<this->Size()) //down two, right one
        if(this->getSquare(i+2,j+1) != EMPTY)
            return true;

    if(i+1<this->Size() && j+2<this->Size()) //down one, right two
        if(this->getSquare(i+1,j+2) != EMPTY)
            return true;

   //is someone attacking the knight
   return this->isAttacked(pos, KNIGHT);
}

bool Board::isKingAttacking(Position pos){
    //king is placed fifth in order
    int i=pos.row, j=pos.col;
    if(j-1>=0)//left one
        if(this->getSquare(pos.row, j-1) != EMPTY)
            return true;

    if(i-1>=0 && j-1>=0)//up one, left one
        if(this->getSquare(i-1, j-1) != EMPTY)
            return true;

    if(i+1<this->Size() && j-1>=0)//down one, left one
        if(this->getSquare(i+1, j-1) != EMPTY)
            return true;

    if(i-1>=0)//up one
        if(this->getSquare(i-1, pos.col) != EMPTY)
            return true;

    if(i-1>=0 && j+1<this->Size())//up one, right one
        if(this->getSquare(i-1, j+1) != EMPTY)
            return true;

    if(j+1<this->Size())//rigth one
        if(this->getSquare(pos.row, j+1) != EMPTY)
            return true;

    if(i+1<this->Size() && j+1<this->Size())//down one, right one
        if(this->getSquare(i+1, j+1) != EMPTY)
            return true;

    if(i+1<this->Size())//down one
        if(this->getSquare(i+1, pos.col) != EMPTY)
            return true;

    //is someone attacking the king
    return this->isAttacked(pos, KING);

}

bool Board::isValid(Position pos, int placed, int numOfQueens, int numOfRooks, int numOfBishops, int numOfKnights, int numOfKings, int total){
    //if it's not possible to place at least half size of rows, figures, in first half of board, then we cannot place remaining figures on second half of board
    //for example we will put at least 4 queens in first 4 rows of 8x8 board
    if(placed<this->Size()/2 && pos.row>=this->Size()/2) return false;

    //if we dont have enough rows for queens and rooks, there is no solution for that case
    //for example if we are at fifth row on 8x8 board, and there are 5 queens and rooks left
    if(this->Size()-pos.row < numOfQueens + numOfRooks - placed) return false;

    //queens, rooks, bishops, knights, kings, in that order
    if(placed<total-numOfRooks-numOfBishops-numOfKnights-numOfKings) return !this->isAttacking(pos, QUEEN);
    else if(placed<total-numOfBishops-numOfKnights-numOfKings) return !this->isAttacking(pos, ROOK);
    else if(placed<total-numOfKnights-numOfKings) return !this->isAttacking(pos, BISHOP);
    else if(placed<total-numOfKings) return !this->isAttacking(pos, KNIGHT);
    else if(placed<total) return !this->isAttacking(pos, KING);

}

bool Board::place(int placed, int numOfQueens, int numOfRooks, int numOfBishops, int numOfKnights, int numOfKings, int total, Position pos=Position(0,0)){
    if (placed >= total) //if all figures are placed, we have solution
      return true;

    for(int i=0;i<this->Size();i++){
        for(int j=0;j<this->Size();j++){
            if(this->getSquare(Position(i,j)) == EMPTY
                && this->isValid(Position(i,j), placed, numOfQueens, numOfRooks, numOfBishops, numOfKnights, numOfKings, total)){

                if(placed<numOfQueens)
                    this->setSquare(QUEEN, Position(i,j));
                else if(placed<numOfQueens+numOfRooks)
                    this->setSquare(ROOK, Position(i,j));
                else if(placed<total-numOfKnights-numOfKings)
                    this->setSquare(BISHOP, Position(i,j));
                else if(placed<total-numOfKings)
                    this->setSquare(KNIGHT, Position(i,j));
                else if(placed<total)
                    this->setSquare(KING, Position(i,j));

                if(this->place(placed+1, numOfQueens, numOfRooks, numOfBishops, numOfKnights, numOfKings, total, Position(i, j+1)))
                    return true;

                this->setSquare(EMPTY, Position(i,j));
            }
        }
    }
   return false;
}

void Board::placeNFigures(int numOfQueens, int numOfRooks, int numOfBishops, int numOfKnights, int numOfKings){
    int noQ=numOfQueens,noR=numOfRooks,noB=numOfBishops,noN=numOfKnights,noK=numOfKings;
    if(!noQ && !noR && !noB && !noN && !noK){
        cout<<"Enter number of queens, rooks, bishops, knights and kings, in that order: "<<endl;
        cin>>noQ>>noR>>noB>>noK>>noN;
    }
    if ( this->place(0, noQ, noR, noB, noN, noK, noQ+noR+noB+noN+noK) == false ) {
      cout << "Solution does not exist!";
      return;
    }
    cout << "Solution found: ";
    this->printBoard();
    return;
}
