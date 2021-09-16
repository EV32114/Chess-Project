#pragma once
#include <iostream>
#include "Piece.h"
#include "Board.h"
#include <String>

class Piece;
class Board;

using std::string;

class Rook : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class rook.
	/// </summary>
	/// <param name="type"> If the rook is black or white </param>
	Rook(char type);

	/// <summary>
	/// This function checks if a move that is proformed on a rook matches the way that a rook moves.
	/// </summary>
	/// <param name="src"> The position of the rook that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the rook to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(const int* src, const int* dest, const Board& board) const;
	string* getValidMoves(const int* src, const Board& board) const;
};
