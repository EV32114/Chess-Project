#include "Piece.h"

Piece::Piece(const char type)
{
	this->_type = type;
    this->_hasMoved = false;
}

void Piece::setType(char type)
{
	this->_type = type;
}

char Piece::getType() const
{
	return this->_type;
}

bool Piece::getHasMoved() const
{
    return this->_hasMoved;
}

void Piece::setHasMoved(const bool hasMoved)
{
    this->_hasMoved = hasMoved;
}
