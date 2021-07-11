#pragma once
#include <iostream>
#include "Piece.h"
#include "Board.h"
class Board;

class EmptySquare : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class EmptySquare.
	/// </summary>
	/// <param name="type"> An empty square char - '#' </param>
	EmptySquare(char type);

	virtual bool isValidPieceMove(const int* src, const int* dest, const Board& board) const;
};
