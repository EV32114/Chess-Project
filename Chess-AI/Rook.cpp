#include "Rook.h"
#include "HandleGame.h"
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
