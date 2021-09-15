#include "King.h"
#include "HandleGame.h"
class Piece;

King::King(char type, int pos1, int pos2) : Piece(type)
{
    this->_position[0] = pos1;
    this->_position[1] = pos2;
}

int* King::getPosition() const
{
    return (int*)this->_position;
}

void King::setPosition(const int* position)
{
    this->_position[0] = position[0];
    this->_position[1] = position[1];
}

bool King::isValidPieceMove(const int* src, const int* dest, const Board& board) const
{
    int subX = src[0] - dest[0];
    int subY = src[1] - dest[1];

    if (abs(subX) > 1 || abs(subY) > 1)
    {
        return false;
    }

    return true;
}
