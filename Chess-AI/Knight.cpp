#include "Knight.h"
#include <String>
using std::string;


Knight::Knight(char type, int* pos) : Piece(type, pos)
{
}

bool Knight::isValidPieceMove(int* src, const int* dest, const Board& board) const
{
	int subX = abs(src[0] - dest[0]);
	int subY = abs(src[1] - dest[1]);

	if ((subX == 2 && subY == 1) || (subX == 1 && subY == 2))
	{
		return true;
	}

	return false;
}

std::vector<std::string> Knight::getValidMoves(int* src, const Board& board) const
{
	std::vector<string> validMoves;
	
	/* We check each of the possibiliies, if it's empty or eatable we can move there. */
	if (src[0] + 2 < 8 && src[1] + 1 < 8) {
		if (board.getBoard()[src[0] + 2][src[1] + 1]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] + 2][src[1] + 1]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] + 2][src[1] + 1]->getType())))) {
			validMoves.push_back(std::to_string(src[0] + 2) + std::to_string(src[1] + 1));
		}
	}
	if (src[0] + 2 < 8 && src[1] - 1 >= 0) {
		if (board.getBoard()[src[0] + 2][src[1] - 1]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] + 2][src[1] - 1]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] + 2][src[1] - 1]->getType())))) {
			validMoves.push_back(std::to_string(src[0] + 2) + std::to_string(src[1] - 1));
		}
	}

	if (src[0] - 2 >= 0 && src[1] + 1 < 8) {
		if (board.getBoard()[src[0] - 2][src[1] + 1]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] - 2][src[1] + 1]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] - 2][src[1] + 1]->getType())))) {
			validMoves.push_back(std::to_string(src[0] - 2) + std::to_string(src[1] + 1));
		}
	}

	if (src[0] - 2 >= 0 && src[1] - 1 >= 0) {
		if (board.getBoard()[src[0] - 2][src[1] - 1]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] - 2][src[1] - 1]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] - 2][src[1] - 1]->getType())))) {
			validMoves.push_back(std::to_string(src[0] - 2) + std::to_string(src[1] - 1));
		}
	}

	if (src[1] + 2 < 8 && src[0] + 1 < 8) {
		if (board.getBoard()[src[0] + 1][src[1] + 2]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] + 1][src[1] + 2]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] + 1][src[1] + 2]->getType())))) {
			validMoves.push_back(std::to_string(src[0] + 1) + std::to_string(src[1] + 2));
		}
	}

	if (src[0] + 1 < 8 && src[1] - 2 >= 0) {
		if (board.getBoard()[src[0] + 1][src[1] - 2]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] + 1][src[1] - 2]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] + 1][src[1] - 2]->getType())))) {
			validMoves.push_back(std::to_string(src[0] + 1) + std::to_string(src[1] - 2));
		}
	}

	if (src[0] - 1 >= 0 && src[1] + 2 < 8) {
		if (board.getBoard()[src[0] - 1][src[1] + 2]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] - 1][src[1] + 2]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] - 1][src[1] + 2]->getType())))) {
			validMoves.push_back(std::to_string(src[0] - 1) + std::to_string(src[1] + 2));
		}
	}

	if (src[0] - 1 >= 0 && src[1] - 2 >= 0) {
		if (board.getBoard()[src[0] - 1][src[1] - 2]->getType() == EMPTY_SQUARE || ((_isWhite && islower(board.getBoard()[src[0] - 1][src[1] - 2]->getType())) || (!_isWhite && isupper(board.getBoard()[src[0] - 1][src[1] - 2]->getType())))) {
			validMoves.push_back(std::to_string(src[0] - 1) + std::to_string(src[1] - 2));
		}
	}
	return validMoves;
}
