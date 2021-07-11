#include "EmptySquare.h"

EmptySquare::EmptySquare(char type) : Piece(type)
{
}

bool EmptySquare::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
	return false;
}
