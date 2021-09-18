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
    bool isWhite = isupper(this->_type);
    int sign = isWhite ? 1 : -1;
    int nIndex = 0;
    string* validMoves = new string[NUM_OF_MOVES]{ "" };
    /*
        Front row = row that takes a + index to get to.
        Back row, obviously, is the opposite.
    */
    bool backRowBlocked = false; // will be used to determine whether we have an interest to check the back rows.
    bool backColBlocked = false; // will be used to determine whether we have an interest to check the back columns.
    bool frontRowBlocked = false; // will be used to determine whether we have an interest to check the front rows.
    bool frontColBlocked = false; // will be used to determine whether we have an interest to check the front columns.

    for (int i = 1; i < 8; i++) {
        for (int j = 1; j < i; j++) {
            if (src[0] + j < 8 && board.getBoard()[src[0] + j][src[1]]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                frontRowBlocked = true;
            if (src[1] + j < 8 && board.getBoard()[src[0]][src[1] + j]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                frontColBlocked = true;
            if (src[0] - j >= 0 && board.getBoard()[src[0] - j][src[1]]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                backRowBlocked = true;
            if (src[1] - j >= 0 && board.getBoard()[src[0]][src[1] - j]->getType() != EMPTY_SQUARE) // if it tries to pass an occupied space, we break.
                backColBlocked = true;
        }
        /*
            In the following if statements, we check whether a certain square which isn't blocked is either an empty square or an enemy piece.
            If it is indeed one of them we add the move to the valid moves and increment the index.
        */
        if ((src[0] + i) < 8) {
            if (board.getBoard()[src[0] + i][src[1]]->getType() == EMPTY_SQUARE ||
                ((isupper(board.getBoard()[src[0] + i][src[1]]->getType()) && !isWhite) || (islower(board.getBoard()[src[0] + i][src[1]]->getType()) && isWhite))) {
                validMoves[nIndex] = std::to_string(src[0] + i) + std::to_string(src[1]);
                nIndex++;
            }
        }
        if ((src[0] - i) >= 0) {
            if (board.getBoard()[src[0] - i][src[1]]->getType() == EMPTY_SQUARE ||
                ((isupper(board.getBoard()[src[0] - i][src[1]]->getType()) && !isWhite) || (islower(board.getBoard()[src[0] - i][src[1]]->getType()) && isWhite))) {
                validMoves[nIndex] = std::to_string(src[0] - i) + std::to_string(src[1]);
                nIndex++;
            }
        }
    }
    return validMoves;
}
