#include "Evaluate.h"

int main()
{
	// cout << Evaluate::evalPos("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") << endl;
	cout << Evaluate::evalPos("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0") << endl;
	Board board("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");
	

	return 0;
}
