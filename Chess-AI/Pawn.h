#pragma once
#include <iostream>
#include "Piece.h"
#include "Board.h"
#include <String>

class Board;
using std::string;

#define BLACK_PAWN_ROW 1
#define WHITE_PAWN_ROW 6

class Pawn : public Piece
{
public:
	/// <summary>
	/// This function is the constructor of the class Pawn.
	/// </summary>
	/// <param name="type"> If the pawn is black or white </param>
	Pawn(char type, int* pos);

	/// <summary>
	/// This function checks if a move that is proformed on a pawn matches the way that a pawn moves.
	/// </summary>
	/// <param name="src"> The position of the pawn that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the pawn to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(int* src, const int* dest, const Board& board) const;

private:
	/// <summary>
	/// This function gets information about the pawn:
	/// It gets the char after the pawn, gets the initial row of the pawn
	/// and checks if the pawn is going backwards.
	/// </summary>
	/// <param name="board"> The game board </param>
	/// <param name="initialRow"> A pointer to the initial row of the pawns </param>
	/// <param name="afterSrc"> A pointer to the char after the src char </param>
	/// <param name="src"> The position of the pawn to be moved </param>
	/// <param name="dest"> Where to move the pawn to </param>
	/// <returns> If the pawn tried to move backwards </returns>
	bool getPawnInfo(const Board& board, int* initialRow, Piece** afterSrc, const int* src, const int* dest) const;
	virtual std::vector<std::string> getValidMoves(int* src, const Board& board) const;
};
