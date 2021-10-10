#include "Piece.h"

Piece::Piece(const char type, int* pos)
{
	this->_type = type;
    this->_hasMoved = false;
	this->_isWhite = isupper(type);
	this->_position = pos;
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

bool Piece::getIsWhite() const {
	return this->_isWhite;
}


void Piece::setHasMoved(const bool hasMoved)
{
    this->_hasMoved = hasMoved;
}

void Piece::setPos(const int* pos)
{
	this->_position = (int*)pos;
}

int* Piece::getPos()
{
	return this->_position;
}
