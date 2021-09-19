#ifndef __PIECE_H__
#define __PIECE_H__

#include <iostream>
#include "Board.h"
#include <vector>

#define BLACK 1
#define WHITE 0

class Board;

class Piece
{
protected:
	char _type;
	bool _hasMoved;
	bool _isWhite;

public:
	/// <summary>
	/// This function is the constructor of the class Piece.
	/// </summary>
	/// <param name="type"> The type of the piece </param>
	Piece(const char type);

	/// <summary>
	/// This function sets a new type to _type.
	/// </summary>
	/// <param name="type"> The new type </param>
	void setType(char type);

	/// <summary>
	/// This function gets the type of the piece.
	/// </summary>
	/// <returns> The piece type </returns>
	char getType() const;

	/// <summary>
	/// This function returns true if the piece is white.
	/// </summary>
	/// <returns> true if the piece is white </returns>
	bool getIsWhite() const;
	
	/// <summary>
	/// This function checks if a move that is proformed on a piece matches the way that the piece moves.
	/// </summary>
	/// <param name="src"> The position of the piece that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the piece to </param>
	/// <param name="board"> The game board </param>
	/// <returns> If the move is valid or not </returns>
	virtual bool isValidPieceMove(const int* src, const int* dest, const Board& board) const = 0;

	virtual std::vector<std::string> getValidMoves(const int* src, const Board & board) const = 0;

	bool getHasMoved() const;
	void setHasMoved(const bool hasMoved);
};

#endif // !__PIECE_H__
