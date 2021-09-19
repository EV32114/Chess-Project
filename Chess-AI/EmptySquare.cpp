#include "EmptySquare.h"

EmptySquare::EmptySquare(char type) : Piece(type)
{
}

bool EmptySquare::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
	return false;
}

std::vector<std::string> EmptySquare::getValidMoves(const int* src, const Board& board) const
{
	return std::vector<std::string>();
}
