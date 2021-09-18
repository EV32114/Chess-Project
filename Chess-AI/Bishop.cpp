#include "Bishop.h"
#include "Board.h"

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

string* Bishop::getValidMoves(const int* src, const Board& board) const {
    bool isWhite = isupper(this->_type);
    int sign = isWhite ? 1 : -1;
    string* validMoves = new string[NUM_OF_MOVES] { "" };
    int nIndex = 0;
    for (int i = 1; i < NUM_OF_MOVES; i++) {
        for (int j = 1; j < i; j++) {
            if (src[0] + j < 8 && src[1] + j < 8) {
                if ((src[0] + j * sign) < 8 && (src[1] + j * sign) < 8 && (src[1] + j * sign) >= 8 && (src[0] + j * sign) >= 8) {
                    if (board.getBoard()[src[0] + (j * sign)][src[1] + (j * sign)]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                        return validMoves;
                }
            }
        }
        if ((src[0] + i * sign) < 8 && (src[0] + i * sign) >= 0 && (src[1] + i * sign) < 8 && (src[1] + i * sign) >= 0) {
            if (board.getBoard()[src[0] + (i * sign)][src[1] + (i * sign)]->getType() == EMPTY_SQUARE
                || ((board.getBoard()[src[0] + (i * sign)][src[1] + (i * sign)]->getType() == 'K' && !isWhite) || (board.getBoard()[src[0] + (i * sign)][src[1] + (i * sign)]->getType() == 'k') && isWhite)) {
                validMoves[nIndex] = std::to_string(src[0] + i * sign) + std::to_string(src[1] + i * sign); // space is empty or there's a piece there, and we can move there.
                nIndex++;
            }
        }
    }
    return validMoves;
}
