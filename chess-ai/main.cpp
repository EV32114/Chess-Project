#include "Evaluate.h"

int main()
{
	// cout << Evaluate::evalPos("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1") << endl;

	// Board board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	Board board("8/8/5p2/1P1Kk12/8/2r5/8/7R w - - 0 0");
	cout << Evaluate::attackKingZone(board, true) << endl;
	board.printBoard();
	
	

	return 0;
}
