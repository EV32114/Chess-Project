#pragma once
#include <iostream>
#include "Piece.h"
#include "Board.h"
class Board;

class Knight : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class knight.
	/// </summary>
	/// <param name="type"> If the knight is black or white </param>
	Knight(char type);

	/// <summary>
	/// This function checks if a move that is proformed on a knight matches the way that a knight moves.
	/// </summary>
	/// <param name="src"> The position of the knight that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the knight to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(const int* src, const int* dest, const Board& board) const;

	virtual std::string* getValidMoves(const int* src, const Board& board) const;
};
