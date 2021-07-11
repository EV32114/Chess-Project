#include "Bishop.h"

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
