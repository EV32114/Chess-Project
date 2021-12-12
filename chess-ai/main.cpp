#include "Evaluate.h"

int main()
{
	// cout << Evaluate::evalPos("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1") << endl;

	// Board board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	// cout << Evaluate::attackKingZone(board, true) << endl;
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	board.printBoard();
	int x[2] = { 7,7 };
	cout << Evaluate::isOpenFile(board, true, x);
	
	

	return 0;
}
