#include "Knight.h"
#include <String>
using std::string;

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
	bool isWhite = isupper(this->_type);
	string* validMoves = new string[NUM_OF_MOVES]{ "" };
	int nIndex = 0;
	if (src[0] + 2 < 8) {
		if (board.getBoard()[src[0] + 2][src[1] + 1]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] + 2][src[1] + 1]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] + 2][src[1] + 1]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] + 2) + std::to_string(src[1] + 1);
			++nIndex;
		}
	}
	if (src[0] + 2 < 8 && src[1] - 1 >= 0) {
		if (board.getBoard()[src[0] + 2][src[1] - 1]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] + 2][src[1] - 1]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] + 2][src[1] - 1]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] + 2) + std::to_string(src[1] - 1);
			++nIndex;
		}
	}

	if (src[0] - 2 >= 0 && src[1] + 1 < 8) {
		if (board.getBoard()[src[0] - 2][src[1] + 1]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] - 2][src[1] + 1]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] - 2][src[1] + 1]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] - 2) + std::to_string(src[1] + 1);
			++nIndex;
		}
	}

	if (src[0] - 2 >= 0 && src[1] - 1 >= 0) {
		if (board.getBoard()[src[0] - 2][src[1] - 1]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] - 2][src[1] - 1]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] - 2][src[1] - 1]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] - 2) + std::to_string(src[1] + 1);
			++nIndex;
		}
	}

	if (src[1] + 2 < 8) {
		if (board.getBoard()[src[0] + 1][src[1] + 2]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] + 1][src[1] + 2]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] + 1][src[1] + 2]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] + 1) + std::to_string(src[1] + 2);
			++nIndex;
		}
	}

	if (src[0] + 1 < 8 && src[1] - 2 >= 0) {
		if (board.getBoard()[src[0] + 1][src[1] - 2]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] + 1][src[1] - 2]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] + 1][src[1] - 2]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] + 1) + std::to_string(src[1] - 2);
			++nIndex;
		}
	}

	if (src[0] - 1 >= 0 && src[1] + 2 < 8) {
		if (board.getBoard()[src[0] - 1][src[1] + 2]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] - 1][src[1] + 2]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] - 1][src[1] + 2]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] - 1) + std::to_string(src[1] + 2);
			++nIndex;
		}
	}

	if (src[0] - 1 >= 0 && src[1] - 2 >= 0) {
		if (board.getBoard()[src[0] - 1][src[1] - 2]->getType() == EMPTY_SQUARE || ((isWhite && islower(board.getBoard()[src[0] - 1][src[1] - 2]->getType())) || (!isWhite && isupper(board.getBoard()[src[0] - 1][src[1] - 2]->getType())))) {
			validMoves[nIndex] = std::to_string(src[0] - 1) + std::to_string(src[1] - 2);
			++nIndex;
		}
	}
	return validMoves;
}
