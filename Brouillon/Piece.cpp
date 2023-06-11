#include "Piece.h"

using namespace std;

bool checkCheck(Board board, int turn)
{
    // Check if the king is in check
    Pos king_pos;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getPiece(i, j) == 6 * turn) {
                king_pos.x = i;
                king_pos.y = j;
            }
        }
    }
    Piece test;
    vector<Pos> all_moves = test.getAllMovesE(board);
    for (int i = 0; i < all_moves.size(); i++) {
        if (all_moves[i].x == king_pos.x && all_moves[i].y == king_pos.y) {
            return true;
        }
    }
    return false;
}

bool checkCheckMate(Board board)
{
    // Checks if the king is in checkmate
    // Will get each opponent's piece by exploring the board, get its moves, check if both moves and kills are empty
    // If no move is possible, returns true
    // else returns false
    int turn = board.getTurn();
    int opponent = -turn;
    board.switchTurn();
    // Get all the opponent's pieces
    vector<Pos> opponent_pieces;
    Pos pos;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            pos.x = i;
            pos.y = j;
            if (board.getPiece(i, j) * turn < 0) {
                opponent_pieces.push_back(pos);
            }
        }
    }
    // For each piece, get its moves and kills
    // If both are empty, checkmate = true
    // else checkmate = false

    for (int i = 0; i < opponent_pieces.size(); i++) {
        Piece piece(board.getPiece(opponent_pieces[i].x, opponent_pieces[i].y), opponent_pieces[i].x, opponent_pieces[i].y);
        piece.getMoves(board, false);
        if (piece.moves.size() != 0 || piece.kills.size() != 0) {
            return false;
        }
    }
    return true;
}

Piece::Piece(int id, int x, int y)
{
    this->id = id;
    pos.x = x;
    pos.y = y;

}

Piece::Piece()
{

}

Piece::~Piece()
{

}
vector<Pos> Piece::getAllMovesE(Board board) {
    vector<Pos> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.table[i][j] != 0) {
                if (!board.checkTurn(board.table[i][j])) {
                    Piece piece(board.table[i][j], i, j);
                    piece.getMoves(board, true);
                    moves.insert(moves.end(), piece.moves.begin(), piece.moves.end());
                    moves.insert(moves.end(), piece.kills.begin(), piece.kills.end());
                }
            }
        }
    }
    return moves;
}
Pos Piece::getPos()
{
    return pos;
}

void Piece::setPos(Pos pos, Board& board)
{
    // Vérifie si le joueur essaie d'attraper l'en passant
    if (board.en_passant_killed.x == pos.x && board.en_passant_killed.y == pos.y) {
        board.setPiece(board.en_passant.x, board.en_passant.y, 0);
        board.setPiece(pos.x, pos.y, id);
        board.setPiece(this->pos.x, this->pos.y, 0);
        this->pos = pos;
        board.en_passant = { -1,-1 };
        board.en_passant_killed = { -1,-1 };
        board.en_passant_id = 0;
    }
    // Vérifie si le roi a bougé et changer la valeur de petit_roque_B et grand_roque_B ou petit_roque_N et grand_roque_N


    // Vérifie si le joueur veut faire un petit roque ou un grand roque
    if (id == 6) {
        if (board.petit_roque_B && pos.x == 6 && pos.y == 7) {
            board.setPiece(5, 7, 2);
            board.setPiece(7, 7, 0);
            board.setPiece(6, 7, 6);
            board.setPiece(4, 7, 0);
            cout << "Petit roque effectué" << endl;
        }
        else if (board.grand_roque_B && pos.x == 2 && pos.y == 7) {
            board.setPiece(3, 7, 2);
            board.setPiece(0, 7, 0);
            board.setPiece(2, 7, 6);
            board.setPiece(4, 7, 0);
            cout << "Grand roque effectué" << endl;
        }
        else
        {
            board.petit_roque_B = 0;
            board.grand_roque_B = 0;
        }
    }
    else if (id == -6) {
        if (board.petit_roque_N && pos.x == 6 && pos.y == 0) {
            board.setPiece(5, 0, -2);
            board.setPiece(7, 0, 0);
            board.setPiece(6, 0, -6);
            board.setPiece(4, 0, 0);
            cout << "Petit roque effectué" << endl;
        }
        else if (board.grand_roque_N && pos.x == 2 && pos.y == 0) {
            board.setPiece(3, 0, -2);
            board.setPiece(0, 0, 0);
            board.setPiece(2, 0, -6);
            board.setPiece(4, 0, 0);
            cout << "Grand roque effectué" << endl;
        }
        else
        {
            board.petit_roque_N = 0;
            board.grand_roque_N = 0;
        }
    }
    // Vérifie si la tour a bougé et changer la valeur de petit_roque_B ou petit_roque_N
    else if (id == 2) {
        if (pos.x == 0) board.grand_roque_B = 0;
        if (pos.x == 7) board.petit_roque_B = 0;
        board.setPiece(pos.x, pos.y, id);
    }
    else if (id == -2) {
        if (pos.x == 0) board.grand_roque_N = 0;
        if (pos.x == 7) board.petit_roque_N = 0;
        board.setPiece(pos.x, pos.y, id);
    }
    else if ((id == 1 || id == -1)) {
        // If the pawn has moved two squares and is in the starting position, it can be captured en passant
        if (pos.y - this->pos.y == 2 && this->pos.y == 1) {
            board.en_passant = pos;
            board.en_passant_id = 1;
            board.en_passant_killed = { this->pos.x, this->pos.y + 1 };
            board.count = 2;
        }
        else if (pos.y - this->pos.y == -2 && this->pos.y == 6) {
            board.en_passant = pos;
            board.en_passant_id = -1;
            board.en_passant_killed = { this->pos.x, this->pos.y - 1 };
            board.count = 2;
        }


        board.setPiece(pos.x, pos.y, id);
    }
    else {
        board.setPiece(pos.x, pos.y, id);
    }
    this->pos = pos;

    if (board.count != 0)
        board.count--;
    else
    {

        // removes the en passant square
        board.en_passant = { -1,-1 };
        board.en_passant_id = 0;
        board.en_passant_killed = { -1,-1 };
    }
    bool opponent_check = false;
    // Creates a board copy with the new move, and checks if the opponent king is in check
    Board board_copy = board;
    board_copy.setPiece(pos.x, pos.y, id);
    getMoves(board_copy, true);
    // checks if the opponent king is in one of the kill moves
    for (int i = 0; i < kills.size(); i++) {
        if (board_copy.table[kills[i].x][kills[i].y] == (board_copy.getTurn() == -1 ? 6 : -6)) {
            opponent_check = true;
            break;
        }
    }

    board.check = opponent_check;
    if (opponent_check)
    {
        board.checkMate = checkCheckMate(board_copy);
    }
}



void Piece::getMoves(Board board, bool checks)
{
    int check_id = id;
    if (id < 0) check_id = -id;

    switch (check_id) {
    case 1:
        addPawnMoves(pos, board, checks);
        break;
    case 2:
        // Rook
        addRookMoves(pos, board, checks);
        break;
    case 3:
        // Knight
        addKnightMoves(pos, board, checks);
        break;
    case 4:
        // Bishop
        addBishopMoves(pos, board, checks);
        break;
    case 5:
        // Queen
        addQueenMoves(pos, board, checks);
        break;
    case 6:
        // King
        addKingMoves(pos, board, checks);
        break;
    default:
        break;
    }
    // remove the moves that checks the king 
    // create a copy of the board and move the piece to the move position
    if (!checks) {
        for (int i = 0; i < moves.size(); i++) {
            Board copy_board = board;
            copy_board.setPiece(moves[i].x, moves[i].y, copy_board.table[pos.x][pos.y]);
            copy_board.setPiece(pos.x, pos.y, 0);

            if (checkCheck(copy_board, copy_board.getTurn())) {
                moves.erase(moves.begin() + i);
                i--;
            }
        }

        // remove the kill moves that checks the king
        for (int i = 0; i < kills.size(); i++) {
            Board copy_board = board;
            copy_board.setPiece(kills[i].x, kills[i].y, copy_board.table[pos.x][pos.y]);
            copy_board.setPiece(pos.x, pos.y, 0);

            if (checkCheck(copy_board, copy_board.getTurn())) {
                kills.erase(kills.begin() + i);
                i--;
            }
        }


    }
}

bool Piece::checkMove(Pos move, Board board)
{
    // Check if the move is in the moves vector
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].x == move.x && moves[i].y == move.y) return true;
    }

    // Check if the move is in the kills vector
    for (int i = 0; i < kills.size(); i++) {
        if (kills[i].x == move.x && kills[i].y == move.y) return true;
    }

    return false;
}

int Piece::getId()
{
    return id;
}

void Piece::addPawnMoves(Pos mv, Board board, bool checks)
{
    if (!checks)
    {
        // check if there's at least a piece in front of the pawn
        if (board.table[pos.x][pos.y + (-1 * board.turn)] == 0) {
            // check if the pawn is at the starting position
            if ((pos.y == 1 && board.getTurn() == -1) || (pos.y == 6 && board.getTurn() == 1)) {
                // check if there's a piece 2 squares in front of the pawn
                if (board.table[pos.x][pos.y + (-2 * board.turn)] == 0) {
                    moves.push_back({ pos.x, pos.y + (-2 * board.turn) });
                }
            }
            moves.push_back({ pos.x, pos.y + (-1 * board.turn) });
        }


        // check if the en passant square is in the pawn's range
        if (board.en_passant_killed.x == pos.x + 1 || board.en_passant_killed.x == pos.x - 1) {
            if (board.en_passant_killed.y == pos.y + (-1 * board.turn)) {
                kills.push_back({ board.en_passant_killed.x, board.en_passant_killed.y });
            }
        }
    }

    // check if there's an ennemy piece on the four diagonal squares
    if (pos.x != 0) {
        if (board.table[pos.x - 1][pos.y + (-1 * board.turn)] != 0) {
            if (!board.checkTurn(board.table[pos.x - 1][pos.y + (-1 * board.turn)])) {
                if (checks) moves.push_back({ pos.x - 1, pos.y + (-1 * board.turn) });
                else
                    kills.push_back({ pos.x - 1, pos.y + (-1 * board.turn) });
            }
        }
    }

    if (pos.x != 7) {
        if (board.table[pos.x + 1][pos.y + (-1 * board.turn)] != 0) {
            if (!board.checkTurn(board.table[pos.x + 1][pos.y + (-1 * board.turn)])) {
                if (checks) moves.push_back({ pos.x + 1, pos.y + (-1 * board.turn) });
                else
                    kills.push_back({ pos.x + 1, pos.y + (-1 * board.turn) });
            }
        }
    }
}

void Piece::addRookMoves(Pos mv, Board board, bool checks)
{
    // Rook

    for (int i = pos.y + 1; i < 8; i++) {
        Pos move1 = { pos.x, i };
        if (board.table[move1.x][move1.y] == 0) {
            moves.push_back(move1);
        }
        else
        {

            if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            if (checks) moves.push_back(move1);
            break;
        }
    }

    for (int i = pos.x + 1; i < 8; i++) {
        Pos move1 = { i, pos.y };
        if (board.table[move1.x][move1.y] == 0 && move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0) {
            moves.push_back(move1);
        }
        else
        {
            if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            if (checks) moves.push_back(move1);
            break;
        }
    }

    for (int i = pos.x - 1; i >= 0; i--) {
        Pos move1 = { i, pos.y };
        if (board.table[move1.x][move1.y] == 0 && move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0) {
            moves.push_back(move1);
        }
        else
        {
            if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            if (checks) moves.push_back(move1);

            break;
        }
    }

    for (int i = pos.y - 1; i >= 0; i--) {
        Pos move1 = { pos.x, i };
        if (board.table[move1.x][move1.y] == 0 && move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0) {
            moves.push_back(move1);
        }
        else {
            if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            if (checks) moves.push_back(move1);
            break;
        }
    }

}

void Piece::addKnightMoves(Pos pos, Board board, bool checks)
{
    moves.push_back({ pos.x + 1, pos.y + 2 });
    moves.push_back({ pos.x + 1, pos.y - 2 });
    moves.push_back({ pos.x - 1, pos.y + 2 });
    moves.push_back({ pos.x - 1, pos.y - 2 });
    moves.push_back({ pos.x + 2, pos.y + 1 });
    moves.push_back({ pos.x + 2, pos.y - 1 });
    moves.push_back({ pos.x - 2, pos.y + 1 });
    moves.push_back({ pos.x - 2, pos.y - 1 });

    // remove the moves that are out of the board and the moves that are blocked by other pieces
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].x < 0 || moves[i].x > 7 || moves[i].y < 0 || moves[i].y > 7)
        {
            moves.erase(moves.begin() + i);
            i--;
        }
        else if (!checks && board.table[moves[i].x][moves[i].y] != 0) {
            if (!board.checkTurn(board.table[moves[i].x][moves[i].y])) kills.push_back(moves[i]);
            moves.erase(moves.begin() + i);
            i--;
        }
    }
}

void Piece::addBishopMoves(Pos pos, Board board, bool checks)
{
    for (int i = 0; i < 8; i++) {
        Pos move1 = { pos.x + i + 1, pos.y + i + 1 };
        if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0 && board.table[move1.x][move1.y] == 0) {
            moves.push_back(move1);
        }
        else
        {
            if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0)
            {
                if (checks) moves.push_back(move1);
                else if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            }
            break;
        }
    }

    for (int i = 0; i < 8; i++) {
        Pos move1 = { pos.x + i + 1, pos.y - i - 1 };
        if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0 && board.table[move1.x][move1.y] == 0) {
            moves.push_back(move1);
        }
        else {
            if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0)
            {
                if (checks) moves.push_back(move1);
                else if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            }
            break;
        }
    }

    for (int i = 0; i < 8; i++) {
        Pos move1 = { pos.x - i - 1, pos.y + i + 1 };
        if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0 && board.table[move1.x][move1.y] == 0) {
            moves.push_back(move1);
        }
        else
        {
            if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0)
            {
                if (checks) moves.push_back(move1);
                else if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            }
            break;
        }
    }

    for (int i = 0; i < 8; i++) {
        Pos move1 = { pos.x - i - 1, pos.y - i - 1 };
        if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0 && board.table[move1.x][move1.y] == 0) {
            moves.push_back(move1);
        }
        else {
            if (move1.x <= 7 && move1.x >= 0 && move1.y <= 7 && move1.y >= 0)
            {
                if (checks) moves.push_back(move1);
                else if (!board.checkTurn(board.table[move1.x][move1.y])) kills.push_back(move1);
            }
            break;
        }
    }
}

void Piece::addQueenMoves(Pos pos, Board board, bool checks)
{
    addRookMoves(pos, board, checks);
    addBishopMoves(pos, board, checks);
}

void Piece::addKingMoves(Pos pos, Board board, bool checks)
{
    moves.push_back({ pos.x + 1, pos.y + 1 });
    moves.push_back({ pos.x + 1, pos.y - 1 });
    moves.push_back({ pos.x - 1, pos.y + 1 });
    moves.push_back({ pos.x - 1, pos.y - 1 });
    moves.push_back({ pos.x + 1, pos.y });
    moves.push_back({ pos.x - 1, pos.y });
    moves.push_back({ pos.x, pos.y + 1 });
    moves.push_back({ pos.x, pos.y - 1 });

    // remove the moves that are out of the board and the moves that are blocked by other pieces
    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].x < 0 || moves[i].x > 7 || moves[i].y < 0 || moves[i].y > 7)
        {
            moves.erase(moves.begin() + i);
            i--;
        }
        else if (board.table[moves[i].x][moves[i].y] != 0) {
            if (!board.checkTurn(board.table[moves[i].x][moves[i].y])) kills.push_back(moves[i]);
            moves.erase(moves.begin() + i);
            i--;
        }
    }

    if (!checks)
    {
        vector<Pos> all_moves = getAllMovesE(board);
        for (int i = 0; i < all_moves.size(); i++) {
            for (int j = 0; j < moves.size(); j++) {
                if (all_moves[i].x == moves[j].x && all_moves[i].y == moves[j].y) {
                    moves.erase(moves.begin() + j);
                    j--;
                }
            }
        }
        // remove the kill moves that can be accessed by other pieces
        for (int i = 0; i < kills.size(); i++) {
            for (int j = 0; j < all_moves.size(); j++) {
                if (all_moves[j].x == kills[i].x && all_moves[j].y == kills[i].y) {
                    kills.erase(kills.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }

    // Add king castling moves if the way is clear
    if (board.table[5][pos.y] == 0 && board.table[6][pos.y] == 0 && (board.getTurn() == 1 ? board.petit_roque_B : board.petit_roque_N)) {
        moves.push_back({ 6, pos.y });
    }
    if (board.table[3][pos.y] == 0 && board.table[2][pos.y] == 0 && board.table[1][pos.y] == 0 && (board.getTurn() == 1 ? board.grand_roque_B : board.grand_roque_N)) {
        moves.push_back({ 2, pos.y });
    }
}