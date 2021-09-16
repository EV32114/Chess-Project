#pragma once
#include <iostream>
#include "Piece.h"
#include "Board.h"
class Board;

class Queen : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class queen.
	/// </summary>
	/// <param name="type"> If the queen is black or white </param>
	Queen(char type);

	/// <summary>
	/// This function checks if a move that is proformed on a queen matches the way that a queen moves.
	/// </summary>
	/// <param name="src"> The position of the queen that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the queen to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(const int* src, const int* dest, const Board& board) const;
	string[] Queen::getValidMoves(const int* src, const int* dest, const Board& board) const;
};
