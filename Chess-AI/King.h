#pragma once
#include <iostream>
#include <String>
#include "Piece.h"
#include "Board.h"

class Board;

using std::string;

class King : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class king.
	/// </summary>
	/// <param name="type"> If the king is black or white </param>
	King(char type, int pos1, int pos2);

	/// <summary>
	/// This function returns the position of the king.
	/// </summary>
	/// <returns> The position of the king. </returns>
	int* getPosition() const;

	/// <summary>
	/// This function sets the position of the king.
	/// </summary>
	/// <param name="position"> The new position for the king </param>
	void setPosition(const int* position);

	/// <summary>
	/// This function checks if a move that is proformed on a king matches the way that a king moves.
	/// </summary>
	/// <param name="src"> The position of the king that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the king to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(int* src, const int* dest, const Board& board) const;

	virtual std::vector<std::string> getValidMoves(int* src, const Board& board) const;
};
