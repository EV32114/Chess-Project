#include "EmptySquare.h"

EmptySquare::EmptySquare(char type, int* pos) : Piece(type, pos)
{
}

bool EmptySquare::isValidPieceMove(int* src, const int* dest, const Board& board) const
{
	return false;
}

std::vector<std::string> EmptySquare::getValidMoves(int* src, const Board& board) const
{
	return std::vector<std::string>();
}
