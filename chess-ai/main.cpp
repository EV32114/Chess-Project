#include "Evaluate.h"

int main()
{
	cout << Evaluate::evalPos("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1") << endl;
	Board board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
	board.printBoard();
	
	

	return 0;
}
