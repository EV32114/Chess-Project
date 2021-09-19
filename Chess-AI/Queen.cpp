#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"


Queen::Queen(char type) : Piece(type)
{
}

bool Queen::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    Rook rook('r');
    Bishop bishop('b');
    return rook.isValidPieceMove(src, dest, board) || bishop.isValidPieceMove(src, dest, board);
}

std::vector<string> Queen::getValidMoves(const int* src, const Board& board) const {
    Rook rook('r');
    Bishop bishop('b');
    std::vector<string> validMoves = rook.getValidMoves(src, board);
    std::vector<string> bishopVector = bishop.getValidMoves(src, board);
    validMoves.insert(validMoves.end(), bishopVector.begin(), bishopVector.end());
    return validMoves;
}
