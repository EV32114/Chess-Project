#include "Evaluate.h"

int main()
{
	// cout << Evaluate::evalPos("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") << endl;
	cout << Evaluate::evalPos("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0") << endl;
	Board board("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			cout << board.getBoard()[i][j]->getType();
		}
		cout << endl;
	}

	return 0;
}
