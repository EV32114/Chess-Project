#include "EmptySquare.h"

EmptySquare::EmptySquare(char type) : Piece(type)
{
}

bool EmptySquare::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
	return false;
}

std::string* EmptySquare::getValidMoves(const int* src, const Board& board) const
{
	return nullptr;
}
