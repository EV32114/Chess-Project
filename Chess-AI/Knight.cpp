#include "Knight.h"

Knight::Knight(char type) : Piece(type)
{
}

bool Knight::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
	int subX = abs(src[0] - dest[0]);
	int subY = abs(src[1] - dest[1]);

	if ((subX == 2 && subY == 1) || (subX == 1 && subY == 2))
	{
		return true;
	}

	return false;
}

std::string* Knight::getValidMoves(const int* src, const Board& board) const
{
	return nullptr;
}
