#include "Evaluate.h"
#include "CPipeClient.h"

int main()
{
	Board board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	cout << Evaluate::evalPos(board, true) << endl;
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
