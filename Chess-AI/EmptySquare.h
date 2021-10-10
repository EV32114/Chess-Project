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
	EmptySquare(char type, int* pos);

	virtual bool isValidPieceMove(int* src, const int* dest, const Board& board) const;

	virtual std::vector<std::string> getValidMoves(int* src, const Board& board) const;
private:
	static std::vector<std::string> blackMoves;
	static std::vector<std::string> whiteMoves;
};
