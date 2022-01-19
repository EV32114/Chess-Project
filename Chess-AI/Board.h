#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>

#define BOARD_SIDE 8
#define BOARD_INDEX 2
#define FIRST_LETTER 'a'
#define EMPTY_SQUARE '#'
#define WHITE_IN_CHECK 0
#define BLACK_IN_CHECK 1
#define NO_CHECK -1
#define NUM_OF_MOVES 32

#define B_KING 'k'
#define W_KING 'K'
#define B_ROOK 'r'
#define W_ROOK 'R'
#define B_BISHOP 'b'
#define W_BISHOP 'B'
#define B_QUEEN 'q'
#define W_QUEEN 'Q'
#define B_PAWN 'p'
#define W_PAWN 'P'
#define B_KNIGHT 'n'
#define W_KNIGHT 'N'

class Piece;
class King;

class Board
{
private:
	Piece** _board[BOARD_SIDE];
	King* _blackKing;
	King* _whiteKing;
	int* enPassantSquare;
	int halfMove;
	int fullMove;
	bool castleWhiteKing;
	bool castleWhiteQueen;
	bool castleBlackKing;
	bool castleBlackQueen;
	bool nextTurnWhite;
	
public:
	std::vector<std::string> blackMoves;
	std::vector<std::string> whiteMoves;
	Board();
	/// <summary>
	/// This function is the constructor of the class Board.
	/// </summary>
	/// <param name="strBoard"> A string that contains the board content </param>
	Board(std::string strBoard);

	/// <summary>
	/// This function is the destructor of the class Board.
	/// </summary>
	~Board();

	/// <summary>
	/// This function prints the board.
	/// </summary>
	void printBoard() const;

	/// <summary>
	/// This function returns the board.
	/// </summary>
	/// <returns> The board </returns>
	Piece*** getBoard() const;

	/// <summary>
	/// This function gets the black king.
	/// </summary>
	/// <returns> The black king </returns>
	King* getBlackKing() const;

	/// <summary>
	/// This function gets the white king.
	/// </summary>
	/// <returns> The white king </returns>
	King* getWhiteKing() const;

	/// <summary>
	/// This function moves a piece of the board.
	/// </summary>
	/// <param name="src"> The position of the piece that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the piece to </param>
	/// <param name="toDelete"> If to delete the dest piece </param>
	void movePiece(int* src, const int* dest, bool toDelete);

	/// <summary>
	/// This function converts a position on the graphics board to match the board in the code. 
	/// </summary>
	/// <param name="strIndex"> A position on the graphics board </param>
	/// <returns> A position on the code board </returns>
	static int* convertIndex(std::string strIndex);

	void undoMove(std::string move);

	/// <summary>
	/// This function checks if one of the players is in check.
	/// </summary>
	/// <returns> If a player is in check and which player it is </returns>
	int isInCheck() const;

	/// <summary>
	/// This function checks if one of the players is in mate.
	/// </summary>
	/// <param name="playerInCheck"> The player that is in check </param>
	/// <returns> If the player is in mate </returns>
	int isInMate(bool playerInCheck);

	/// <summary>
	/// This function checks if a castling move is valid.
	/// </summary>
	/// <param name="src"> The position of the piece that the player wants to move </param>
	/// <param name="dest"> Where the player wants to move the piece to </param>
	/// <returns> 9 - if castle is valid, 6 - if not valid move and 2 if the dest is not free </returns>
	int castle(const int* src, const int* dest);

	/// <summary>
	/// These function all check if the squares between the king and the rook are empty and not under attack.
	/// </summary>
	/// <returns> All function return if the result of the checking was true or false </returns>
	/*bool checkBottomLeft();
	bool checkBottomRight();
	bool checkTopLeft();
	bool checkTopRight();*/
};

#endif // !__BOARD_H__
