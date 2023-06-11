#pragma once

struct Pos
{
    int x;
    int y;
};

#include <algorithm>
#include<vector>
#include <utility>

using namespace std;
// The chess board
class Board
{
public:
    Board();
    Board(vector<vector<int>>);
    ~Board();
    void switchTurn();
    int getTurn();
    int getPiece(int, int);
    void setPiece(int, int, int);
    bool checkTurn(int);
    bool getCheckMate();
    bool getCheck() {
		return check;
	}


    vector<vector<int>> getTable() {
		return table;
    }

    void setTable(vector<vector<int>> t) {
        this->table = t;
    }

    Pos getEnPassant() {
		return en_passant;
	}

private:
    // The board
    vector<vector<int>> table;
    int turn = 1;
    friend class Piece;
    friend class GraphicalBoard;
    bool petit_roque_B = 1;
    bool grand_roque_B = 1;
    bool petit_roque_N = 1;
    bool grand_roque_N = 1;

    bool n_check = false;
    bool b_check = false;

    Pos en_passant = { -1,-1 };
    Pos en_passant_killed = { -1,-1 };
    int en_passant_id = 0;
    int count = 0;

    bool checkMate = false;
    bool check = false;

};

