#include "Rook.h"
class HandleGame;


Rook::Rook(char type) : Piece(type)
{
}

bool Rook::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    int tempSrc[BOARD_INDEX] = { src[0], src[1] };
    int tempDest[BOARD_INDEX] = { dest[0], dest[1] };

    if (tempSrc[0] != tempDest[0] && tempSrc[1] != tempDest[1]) // If the rook is not going straight
    {
        return false;
    }

    if (tempSrc[0] == tempDest[0]) // If the rook is going right or left
    {
        if (tempDest[1] < tempSrc[1])
        {
            std::swap(tempSrc[1], tempDest[1]);
        }

        for (int i = tempSrc[1] + 1; i < tempDest[1]; i++)
        {
            if (board.getBoard()[tempSrc[0]][i]->getType() != EMPTY_SQUARE) // If the rook is trying to pass a piece
            {
                return false;
            }
        }
    }
    else // If the rook is going up or down
    {
        if (tempDest[0] < tempSrc[0])
        {
            std::swap(tempSrc[0], tempDest[0]);
        }

        for (int i = tempSrc[0] + 1; i < tempDest[0]; i++)
        {
            if (board.getBoard()[i][tempSrc[1]]->getType() != EMPTY_SQUARE) // If the rook is trying to pass a piece
            {
                return false;
            }
        }
    }

    return true;
}

string* Rook::getValidMoves(const int* src, const Board& board) const {
    int nIndex = 0;
    string* validMoves = new string[NUM_OF_MOVES]{ "" };
    bool rowBlocked = false; // will be used to determine whether we have an interest to check the rows.
    bool colBlocked = false; // will be used to determine whether we have an interest to check the columns.
    for (int i = 1; i < 8; i++) {
        for (int j = 1; j < i; j++) {
            if (board.getBoard()[src[0] + j][src[1]]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                rowBlocked = true;
            if (board.getBoard()[src[0]][src[1] + j]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                colBlocked = true;
        }
        if (!rowBlocked) {
            validMoves[nIndex] = std::to_string(src[0] + i) + std::to_string(src[1]);
        }
        if (!colBlocked) {
            validMoves[nIndex] = std::to_string(src[0]) + std::to_string(src[1] + i);
        }
    }
    return validMoves;
}
