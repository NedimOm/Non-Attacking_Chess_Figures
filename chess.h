#ifndef CHESS_H
#define CHESS_H

#include <vector>

using namespace std;

enum Piece{
    QUEEN = 'Q',
    ROOK = 'R',
    BISHOP = 'B',
    KNIGHT = 'N',
    KING = 'K',
    EMPTY = ' '
};

struct Position {
    int row;
    int col;

    Position(int x, int y) : row(x), col(y){}
};

class Board{
    vector<vector<Piece>> board;

    bool isAttacked(Position, Piece);
    bool isAttacking(Position, Piece);
    bool isQueenAttacking(Position);
    bool isRookAttacking(Position);
    bool isBishopAttacking(Position);
    bool isKnightAttacking(Position);
    bool isKingAttacking(Position);
    bool isValid(Position, int, int, int, int, int, int, int);
    bool place(int, int, int, int, int, int, int, Position);

public:

    Board() : Board(8){}
    Board(int Size);
    vector<vector<Piece>> getBoard(){return board;}
    int Size(){return board.size();}
    void printBoard();
    Piece getSquare(Position pos){return this->board[pos.row][pos.col];}
    Piece getSquare(int row, int col){return this->board[row][col];}
    void setSquare(Piece piece, Position pos){this->board[pos.row][pos.col] = piece;}
    void placeNFigures(int numOfQueens=0, int numOfRooks=0, int numOfBishops=0, int numOfKnights=0, int numOfKings=0);
};

#endif // CHESS_H
