#pragma once
#include <iostream>
#include "Piece.h"
#include <String>

using std::string;

class Bishop : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class bishop.
	/// </summary>
	/// <param name="type"> If the bishop is black or white </param>
	Bishop(char type);

	/// <summary>
	/// This function checks if a move that is proformed on a bishop matches the way that a bishop moves.
	/// </summary>
	/// <param name="src"> The position of the bishop that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the bishop to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(const int* src, const int* dest, const Board& board) const;
	std::vector<string> getValidMoves(const int* src, const Board& board) const;
};
