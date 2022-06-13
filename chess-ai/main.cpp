#pragma comment(lib, "Ws2_32.lib")

#include "Evaluate.h"
#include "Client.h"
#include "WSAInitializer.h"

int main()
{
	WSAInitializer wsaInit;
	Client client;
	client.connectToServer("127.0.0.1", 3000);
	std::string boardMsg;
	std::string bestMove;
	while (true) {
		boardMsg = client.recvMsg(client._clientSocket);
		Board board(boardMsg);
		Evaluate eval;
		eval.getValidMoves(board);
		// GET BEST MOVE
		// Minimax probably doesn't work (we need to look at it), but either way it should be made this way:
		int* bestMove = eval.minimaxRoot(7, board, true);
		std::string move = "";
		char firstLetter = (97 + bestMove[0]);
		char secondLetter = (97 + bestMove[2]);

		move += firstLetter + std::to_string(bestMove[1]) + secondLetter + std::to_string(bestMove[3]);
		client.sendMsg(client._clientSocket, move);
	}
	/*
	// Board board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	// cout << Evaluate::attackKingZone(board, true) << endl;
	srand((unsigned)time(0)); // Generate a random seed.
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	board.printBoard();
	int x[2] = { 7,7 };
	cout << Evaluate::isOpenFile(board, true, x);
	int* moves = Evaluate::generateMove(board, true);
	cout << endl << endl;
	for (int i = 4; i--> 0;) {
		cout << i << endl;
		cout << *(moves + i) << endl;
	}
	
	*/
	/*
	std::string sPipeName(PIPENAME);
	CPipeClient* pClient = new CPipeClient(sPipeName);
	::WaitForSingleObject(pClient->GetThreadHandle(), INFINITE); // to remove before prod
	delete pClient;
	pClient = NULL;*/

	return 0;
}
