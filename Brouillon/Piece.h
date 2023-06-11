#pragma once

#include"Board.h"
#include<iostream>
#include<vector>

using namespace std;

class Piece
{
public:
    Piece(int, int, int);
    Piece();
    ~Piece();
    Pos getPos();
    int getId();
    void setId(int) { 
        this->id = id;
    }
    void setPos(Pos, Board&);
    bool checkMove(Pos, Board);

    // Function for each type of piece that adds the possible moves to the vector
    void addPawnMoves(Pos, Board, bool);
    void addRookMoves(Pos, Board, bool);
    void addKnightMoves(Pos, Board, bool);
    void addBishopMoves(Pos, Board, bool);
    void addQueenMoves(Pos, Board, bool);
    void addKingMoves(Pos, Board, bool);
    void getMoves(Board, bool);

    // Function to get all moves of a board
    vector<Pos> getAllMovesE(Board);
private:
    Pos pos;
    int id;
    std::vector <Pos> moves;
    std::vector <Pos> kills;
    friend class Board;
    friend class GraphicalBoard;
    friend bool checkCheckMate(Board);
};

