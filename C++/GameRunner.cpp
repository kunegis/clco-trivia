#include <stdlib.h>

#include "Game.h"

int main()
{
	srand(time(NULL));
	Game aGame;

	aGame.addPlayer("Chet");
	aGame.addPlayer("Pat");
	aGame.addPlayer("Sue");

	bool notAWinner;

	do {

		aGame.roll(rand() % 5 + 1);

		if (rand() % 9 == 7)
		{
			notAWinner = aGame.wrongAnswer();
		}
		else
		{
			notAWinner = aGame.wasCorrectlyAnswered();
		}
	} while (notAWinner);

	return 0;
}
