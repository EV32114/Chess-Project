#include "Pawn.h"

Pawn::Pawn(char type) : Piece(type)
{
}

bool Pawn::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
	int subX = src[0] - dest[0];
	int subY = src[1] - dest[1];
	int pawnRow = src[0];
	int initialRow = 0;
	Piece* destChar = board.getBoard()[dest[0]][dest[1]];
	Piece* afterSrc = 0;

	if (!this->getPawnInfo(board, &initialRow, &afterSrc, src, dest)) // If the pawn is going backwards
	{
		return false;
	}

	if (destChar->getType() != EMPTY_SQUARE) // If the pawn is eating
	{
		if (subY == 0) // If the pawn is going forward
		{
			return false;
		}
		else if (!(abs(subX) == 1 && abs(subY) == 1)) // If the pawn went more than one step
		{
			return false;
		}
	}
	else
	{
		if (subY != 0) // If the pawn is not going forward
		{
			return false;
		}
		else if (abs(subX) > 1 && pawnRow != initialRow) // If the pawn went more than one step and moved already
		{
			return false;
		}
		else if (abs(subX) > 2) // If the pawn went more that two steps
		{
			return false;
		}
		else if (afterSrc)
		{
			if (afterSrc->getType() != EMPTY_SQUARE) // If the pawn jumped over a piece
			{
				return false;
			}
		}
	}

	return true;
}

bool Pawn::getPawnInfo(const Board& board, int* initialRow, Piece** afterSrc, const int* src, const int* dest) const
{
	int subX = src[0] - dest[0];

	if (isupper(this->_type))
	{
		*initialRow = WHITE_PAWN_ROW;
		if (src[0] - 1 > 0 && src[0] - 1 < BOARD_SIDE)
		{
			*afterSrc = board.getBoard()[src[0] - 1][src[1]];
		}

		if (subX < 0)
		{
			return false;
		}
		return true;
	}
	else
	{
		*initialRow = BLACK_PAWN_ROW;
		if (src[0] + 1 > 0 && src[0] + 1 < BOARD_SIDE)
		{
			*afterSrc = board.getBoard()[src[0] + 1][src[1]];
		}

		if (subX > 0)
		{
			return false;
		}
		return true;
	}
}

std::vector<string> Pawn::getValidMoves(const int* src, const Board& board) const {
	int initialRow = isupper(this->_type) ? WHITE_PAWN_ROW : BLACK_PAWN_ROW;
	int pawnRow = src[0];
	std::vector<string> validMoves;
	if (pawnRow == initialRow) {
		// En Passant is an option!
		if (!_isWhite) {
            if (board.getBoard()[src[0] + 2][src[1]]->getType() == EMPTY_SQUARE || _isWhite != board.getBoard()[src[0] + 2][src[1]]->getIsWhite()) { // going forward two spaces if it has yet to move.
				validMoves.push_back(std::to_string(src[0] + 2) + std::to_string(src[1]));
            }
		}
		else {
			if (board.getBoard()[src[0] - 2][src[1]]->getType() == EMPTY_SQUARE || _isWhite != board.getBoard()[src[0] - 2][src[1]]->getIsWhite()) { // going forward two spaces if it has yet to move.
				validMoves.push_back(std::to_string(src[0] - 2) + std::to_string(src[1]));
			}
		}
	}
	else {
		// En Passant was never an option :(
		;
	}
	if (!_isWhite) {
        if (src[0] + 1 < 8) {
            if (board.getBoard()[src[0] + 1][src[1]]->getType() == EMPTY_SQUARE || _isWhite != board.getBoard()[src[0] + 1][src[1]]->getIsWhite()) { // going forward one space.
                validMoves.push_back(std::to_string(src[0] + 1) + std::to_string(src[1]));
            }
        }

        if (src[0] + 1 < 8 && src[1] + 1 < 8) {
            if (board.getBoard()[src[0] + 1][src[1] + 1]->getType() != EMPTY_SQUARE && _isWhite != board.getBoard()[src[0] + 1][src[1] + 1]->getIsWhite()) { // eating.
                validMoves.push_back(std::to_string(src[0] + 1) + std::to_string(src[1] + 1));
            }
        }

        if (src[0] + 1 < 8 && src[1] - 1 >= 0) {
            if (board.getBoard()[src[0] + 1][src[1] - 1]->getType() != EMPTY_SQUARE && _isWhite != board.getBoard()[src[0] + 1][src[1] - 1]->getIsWhite()) { // eating.
                validMoves.push_back(std::to_string(src[0] + 1) + std::to_string(src[1] - 1));
            }
        }
	}
	
	else {

		if (src[0] - 1 >= 0) {
			if (board.getBoard()[src[0] - 1][src[1]]->getType() == EMPTY_SQUARE || _isWhite != board.getBoard()[src[0] - 1][src[1]]->getIsWhite()) { // going forward one space.
				validMoves.push_back(std::to_string(src[0] - 1) + std::to_string(src[1]));
			}
		}

		if (src[0] - 1 >= 0 && src[1] + 1 < 8) {
			if (board.getBoard()[src[0] - 1][src[1] + 1]->getType() != EMPTY_SQUARE && _isWhite != board.getBoard()[src[0] - 1][src[1] + 1]->getIsWhite()) { // eating.
				validMoves.push_back(std::to_string(src[0] - 1) + std::to_string(src[1] + 1));
			}
		}

		if (src[0] - 1 >= 0 && src[1] - 1 >= 0) {
			if (board.getBoard()[src[0] - 1][src[1] - 1]->getType() != EMPTY_SQUARE && _isWhite != board.getBoard()[src[0] - 1][src[1] - 1]->getIsWhite()) { // eating.
				validMoves.push_back(std::to_string(src[0] - 1) + std::to_string(src[1] - 1));
			}
		}
	}
	
	return validMoves;
}