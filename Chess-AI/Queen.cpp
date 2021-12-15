#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"


Queen::Queen(char type, int* pos) : Piece(type, pos)
{
}

bool Queen::isValidPieceMove(int* src, const int* dest, const Board& board) const
{
    Rook rook('r', src);
    Bishop bishop('b', src);
    return rook.isValidPieceMove(src, dest, board) || bishop.isValidPieceMove(src, dest, board);
}

std::vector<string> Queen::getValidMoves(int* src, const Board& board) const {
	/* The movement of the queen is the movement of a rook and a bishop combined. */
    Rook rook(_isWhite ? 'R' : 'r', src); 
	Bishop bishop(_isWhite ? 'B' : 'b', src);
    std::vector<string> validMoves = rook.getValidMoves(src, board); // Getting the moves of a rook.
    std::vector<string> bishopVector = bishop.getValidMoves(src, board); // Getting the moves of a bishop. 
    validMoves.insert(validMoves.end(), bishopVector.begin(), bishopVector.end()); // Combining them.
    return validMoves;
}
