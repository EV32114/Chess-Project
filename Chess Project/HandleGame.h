#pragma once
#include <iostream>
#include "Board.h"
#include <WinSock2.h>
#include <string>
#include <vector>
class Board;
class Piece;

#define BLACK 1
#define WHITE 0
#define INIT_STR "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0"

enum returnCodes {VALID, CHECK, INVALID_SRC, INVALID_DEST, SELF_CHECK, INVALID_INDEX, INVALID_MOVE, SAME_SRC_AND_DEST, CHECKMATE, CASTLE};

class HandleGame
{
private:
	static bool _currentPlayer; // black - true, white - false

public:
	/// <summary>
	/// This function returns the current player.
	/// </summary>
	/// <returns> The current player (black or white) </returns>
	static bool getCurrentPlayer();

	/// <summary>
	/// This function sets the current player.
	/// </summary>
	/// <param name="color"> The current player (black or white) </param>
	static void setCurrentPlayer(int color);

	/// <summary>
	/// This function runs the main loop of the game.
	/// </summary>
	/// <param name="board"> The game board </param>
	/// <param name="pipe"> A connection between the backend and the frontend </param>
	static void startGame(Board* board, SOCKET* pipe);

	/// <summary>
	/// This function handles a player's turn:
	/// Gets his move, checks if it's valid and returns the fitting code. 
	/// </summary>
	/// <param name="instruction"> The instruction from the graphics </param>
	/// <param name="board"></param>
	/// <returns> The code to send to the graphics </returns>
	static int handleTurn(std::string instruction, Board& board);

	/// <summary>
	/// This function changes the current player according to the number of rounds.
	/// </summary>
	/// <param name="code"> A code that was sent to the graphics at the end of a turn </param>
	/// <param name="roundCounter"> A pointer to the amount of rounds that have been played </param>
	static void changeCurrentPlayer(const int code, int* roundCounter);

	static std::string receiveMsg(SOCKET sock, int len, int offset);
	static void sendMsg(SOCKET sock, const char** buffer, int len);
};
