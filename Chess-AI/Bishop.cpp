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
    string validMoves[NUM_OF_MOVES] = { "" };
    int nIndex = 0;
    for (int i = 1; i < NUM_OF_MOVES; i++) {
        for (int j = 1; j < i; j++) {
            if (board.getBoard()[src[0] + j][src[1] + j]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                return validMoves;
        }
        //if (!(src[0 - i] <= 1 || src[1 - i] <= 1 || src[0 + i] > 8 || src[1 + i] > 8)) {
        //    if (board.getBoard()[src[0] + i][src[1] + i]->getType() != EMPTY_SQUARE) { // it can eat the piece in the certain square.
        //        validMoves[nIndex] = to_string(i) + to_string(j);
        //        nIndex++;
        //    }
        //    else {
        //        validMoves[nIndex] = to_string(i) + to_string(j); // space is empty, and it can move there.
        //        nIndex++;
        //    }
        //}
        validMoves[nIndex] = std::to_string(src[0] + i) + std::to_string(src[1] + i); // space is empty or there's a piece there, and we can move there.
        nIndex++;
    }
    return validMoves;
}
