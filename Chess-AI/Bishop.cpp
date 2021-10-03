#include "Bishop.h"
#include "Board.h"
#include <vector>

Bishop::Bishop(char type) : Piece(type)
{
}

bool Bishop::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    int subX = src[0] - dest[0];
    int subY = src[1] - dest[1];

    if (src[0] == dest[0] || src[1] == dest[1] || abs(subX) != abs(subY)) // If the bishop is not going diagonally
    {
        return false;
    }

    for (int i = 1; i < abs(subX); i++)
    {
        if (subX > 0 && subY > 0)
        {
            if (board.getBoard()[src[0] - i][src[1] - i]->getType() != EMPTY_SQUARE) // If path is not clear
            {
                return false;
            }
        }
        else if (subX > 0 && subY < 0)
        {
            if (board.getBoard()[src[0] - i][src[1] + i]->getType() != EMPTY_SQUARE) // If path is not clear
            {
                return false;
            }
        }
        else if (subX < 0 && subY > 0)
        {
            if (board.getBoard()[src[0] + i][src[1] - i]->getType() != EMPTY_SQUARE) // If path is not clear
            {
                return false;
            }
        }
        else if (subX < 0 && subY < 0)
        {
            if (board.getBoard()[src[0] + i][src[1] + i]->getType() != EMPTY_SQUARE) // If path is not clear
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<string> Bishop::getValidMoves(const int* src, const Board& board) const {
	std::vector<string> validMoves;
	bool breakFlag = false;;
	for (int way = 0; way < 4; way++) {
		breakFlag = false;
		for (int i = 1; i < 8 && !breakFlag; i++) {
			switch (way) {
				case 0:
					if (src[0] + i < 8 && src[1] + i < 8) {
						if (board.getBoard()[src[0] + i][src[1] + i]->getType() == EMPTY_SQUARE) {
							validMoves.push_back(std::to_string(src[0] + i) + std::to_string(src[1] + i));
						}
						else {
							if (_isWhite != board.getBoard()[src[0] + i][src[1] + i]->getIsWhite()) {
								validMoves.push_back(std::to_string(src[0] + i) + std::to_string(src[1] + i));
							}
							breakFlag = true;
						}
					}
					break;
				case 1:
					if (src[0] + i < 8 && src[1] - i >= 0) {
						if (board.getBoard()[src[0] + i][src[1] - i]->getType() == EMPTY_SQUARE) {
							validMoves.push_back(std::to_string(src[0] + i) + std::to_string(src[1] - i));
						}
						else {
							if (_isWhite != board.getBoard()[src[0] + i][src[1] - i]->getIsWhite()) {
								validMoves.push_back(std::to_string(src[0] + i) + std::to_string(src[1] - i));
							}
							breakFlag = true;
						}
					}
					break;
				case 2:
					if (src[0] - i >= 0 && src[1] - i >= 0) {
						if (board.getBoard()[src[0] - i][src[1] - i]->getType() == EMPTY_SQUARE) {
							validMoves.push_back(std::to_string(src[0] - i) + std::to_string(src[1] - i));
						}
						else {
							if (_isWhite != board.getBoard()[src[0] - i][src[1] - i]->getIsWhite()) {
								validMoves.push_back(std::to_string(src[0] - i) + std::to_string(src[1] - i));
							}
							breakFlag = true;
						}
					}
					break;
				case 3:
					if (src[0] - i >= 0 && src[1] + i < 8) {
						if (board.getBoard()[src[0] - i][src[1] + i]->getType() == EMPTY_SQUARE) {
							validMoves.push_back(std::to_string(src[0] - i) + std::to_string(src[1] + i));
						}
						else {
							if (_isWhite != board.getBoard()[src[0] - i][src[1] + i]->getIsWhite()) {
								validMoves.push_back(std::to_string(src[0] - i) + std::to_string(src[1] + i));
							}
							breakFlag = true;
						}
					}
					break;
			}

		}
	}
   
    return validMoves;
}
